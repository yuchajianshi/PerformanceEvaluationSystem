#pragma once
#include "PageBase.h"
#include "GigabitEthernetDevice.h"
#include "afxwin.h"

#define BUTTON_NUM_ONLINE 6
#define BUTTON_NUM_OFFLINE 1

extern const int nLenFrame;

// CPage4 对话框

typedef struct _THREADPARAM
{
	CPageBase* pPage4Dlg;
	_THREADPARAM()
	{
		pPage4Dlg = NULL;
	};

}THREADPARAM,*PTHREADPARAM;

class CPage4 : public CPageBase
{
	DECLARE_DYNAMIC(CPage4)

public:
	CPage4(CWnd* pParent = NULL);		// 标准构造函数
	virtual ~CPage4();

public:
	LPVOID pTempMainDlg;				//主对界面指针
	CGigabitEthernetDevice *pGEDevice;	//千兆网接口设备

public:
	volatile BOOL bThreadStopRecv;		//停止接收标志
	HANDLE hThreadRecv;					//接收线程句柄
	DWORD dwThreadRecvID;				//接收线程ID
	volatile BOOL bThreadStopPlot;		//停止绘图标志
	HANDLE hThreadPlot;					//绘图线程
	DWORD dwThreadPlotID;				//绘图线程ID
	CRect rect_button[6];               //存放几个按钮的位置

	THREADPARAM ThreadRecvParam;		//线程参数

//控件相关变量
public:
	int m_nRecvSize;					//接收包数
	int m_nFramesPerPackage;			//每包包含的帧数
	double m_Carrier;					//载波
	CComboBox m_ModulateMode;			//调制方式
	double m_SymbolRateVal;				//符号速率
	CComboBox m_SymbolRateUnit;			//符号速率单位
	CComboBox m_UploadDataType;			//上传数据类型
	int m_C1;							//滤波系数C1
	int m_C2;							//滤波系数C2
	int c1delta;
	int c2delta;
	double offsetvalue;
	double m_modulatedeep;
	short bandwidth;
	short directpull;						//直抽倍数
	short downsample1;					//第一级CIC下抽倍数
	short downsample2;					//第二级CIC下抽倍数
	
private:
	CButton *m_buttons[BUTTON_NUM_ONLINE];      //所有的按钮

// 对话框数据
	enum { IDD = IDD_PAGE4 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL Create(UINT nIDTemplate, CWnd* pParentWnd = NULL);
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonConfigure();
	afx_msg void OnBnClickedButtonRecvdata();
	afx_msg void OnBnClickedButtonCompar();
	afx_msg void OnBnClickedButtonReset();
	afx_msg void OnBnClickedButtonStopRecv();
	afx_msg void OnBnClickedButtonModulator();
	afx_msg LRESULT OnButtonChanged(WPARAM wParam, LPARAM lParam);
	afx_msg void OnBnClickedCallsimulink();
	void Begintrack();
	void Endtrack();
	void Beginoffset();
	void Endoffset();
	void Channelize();
	void SpectrumAnalyse();
	void DataUpload();
	afx_msg void OnBnClickedTransfer();
	afx_msg void OnBnClickedGmskifdelay();
	unsigned char m_ifdelay;
};
