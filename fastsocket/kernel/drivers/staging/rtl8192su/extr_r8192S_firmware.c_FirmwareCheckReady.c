#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct r8192_priv {TYPE_1__* pFirmware; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {scalar_t__ FWStatus; } ;
typedef  TYPE_1__ rt_firmware ;
typedef  scalar_t__ RT_STATUS ;
typedef  scalar_t__ FIRMWARE_8192S_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_ERR ; 
 int /*<<< orphan*/  COMP_FIRMWARE ; 
 int DMEM_CODE_DONE ; 
 int EMEM_CHK_RPT ; 
 int EMEM_CODE_DONE ; 
 int FWRDY ; 
 int FW_STATUS_LOAD_DMEM ; 
 int FW_STATUS_LOAD_EMEM ; 
 int FW_STATUS_LOAD_IMEM ; 
 scalar_t__ FirmwareEnableCPU (struct net_device*) ; 
 int IMEM_CHK_RPT ; 
 int IMEM_CODE_DONE ; 
 int /*<<< orphan*/  LBKMD_SEL ; 
 int /*<<< orphan*/  LBK_NORMAL ; 
 int LOAD_FW_READY ; 
 int /*<<< orphan*/  RCR ; 
 int RCR_APPFCS ; 
 int RCR_APP_ICV ; 
 int RCR_APP_MIC ; 
 scalar_t__ RT_STATUS_SUCCESS ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  TCR ; 
 int TCR_ICV ; 
 struct r8192_priv* ieee80211_priv (struct net_device*) ; 
 int read_nic_byte (struct net_device*,int /*<<< orphan*/ ) ; 
 int read_nic_dword (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  write_nic_byte (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_nic_dword (struct net_device*,int /*<<< orphan*/ ,int) ; 

bool
FirmwareCheckReady(struct net_device *dev,	u8 LoadFWStatus)
{
	struct r8192_priv 	*priv = ieee80211_priv(dev);
	RT_STATUS	rtStatus = RT_STATUS_SUCCESS;
	rt_firmware	*pFirmware = priv->pFirmware;
	int			PollingCnt = 1000;
	//u8	 	tmpU1b, CPUStatus = 0;
	u8	 	CPUStatus = 0;
	u32		tmpU4b;
	//bool		bOrgIMREnable;

	RT_TRACE(COMP_FIRMWARE, "--->FirmwareCheckReady(): LoadStaus(%d),", LoadFWStatus);

	pFirmware->FWStatus = (FIRMWARE_8192S_STATUS)LoadFWStatus;
	if( LoadFWStatus == FW_STATUS_LOAD_IMEM)
	{
		do
		{//Polling IMEM code done.
			CPUStatus = read_nic_byte(dev, TCR);
			if(CPUStatus& IMEM_CODE_DONE)
				break;

			udelay(5);
		}while(PollingCnt--);
		if(!(CPUStatus & IMEM_CHK_RPT) || PollingCnt <= 0)
		{
			RT_TRACE(COMP_ERR, "FW_STATUS_LOAD_IMEM FAIL CPU, Status=%x\r\n", CPUStatus);
			return false;
		}
	}
	else if( LoadFWStatus == FW_STATUS_LOAD_EMEM)
	{//Check Put Code OK and Turn On CPU
		do
		{//Polling EMEM code done.
			CPUStatus = read_nic_byte(dev, TCR);
			if(CPUStatus& EMEM_CODE_DONE)
				break;

			udelay(5);
		}while(PollingCnt--);
		if(!(CPUStatus & EMEM_CHK_RPT))
		{
			RT_TRACE(COMP_ERR, "FW_STATUS_LOAD_EMEM FAIL CPU, Status=%x\r\n", CPUStatus);
			return false;
		}

		// Turn On CPU
		rtStatus = FirmwareEnableCPU(dev);
		if(rtStatus != RT_STATUS_SUCCESS)
		{
			RT_TRACE(COMP_ERR, "Enable CPU fail ! \n" );
			return false;
		}
	}
	else if( LoadFWStatus == FW_STATUS_LOAD_DMEM)
	{
		do
		{//Polling DMEM code done
			CPUStatus = read_nic_byte(dev, TCR);
			if(CPUStatus& DMEM_CODE_DONE)
				break;

			udelay(5);
		}while(PollingCnt--);

		if(!(CPUStatus & DMEM_CODE_DONE))
		{
			RT_TRACE(COMP_ERR, "Polling  DMEM code done fail ! CPUStatus(%#x)\n", CPUStatus);
			return false;
		}

		RT_TRACE(COMP_FIRMWARE, "DMEM code download success, CPUStatus(%#x)\n", CPUStatus);

//              PollingCnt = 100; // Set polling cycle to 10ms.
              PollingCnt = 10000; // Set polling cycle to 10ms.

		do
		{//Polling Load Firmware ready
			CPUStatus = read_nic_byte(dev, TCR);
			if(CPUStatus & FWRDY)
				break;

			udelay(100);
		}while(PollingCnt--);

		RT_TRACE(COMP_FIRMWARE, "Polling Load Firmware ready, CPUStatus(%x)\n", CPUStatus);

		//if(!(CPUStatus & LOAD_FW_READY))
		//if((CPUStatus & LOAD_FW_READY) != 0xff)
		if((CPUStatus & LOAD_FW_READY) != LOAD_FW_READY)
		{
			RT_TRACE(COMP_ERR, "Polling Load Firmware ready fail ! CPUStatus(%x)\n", CPUStatus);
			return false;
		}

	       //
              // <Roger_Notes> USB interface will update reserved followings parameters later!!
              // 2008.08.28.
              //

	       //
              // <Roger_Notes> If right here, we can set TCR/RCR to desired value
              // and config MAC lookback mode to normal mode. 2008.08.28.
              //
              tmpU4b = read_nic_dword(dev,TCR);
		write_nic_dword(dev, TCR, (tmpU4b&(~TCR_ICV)));

		tmpU4b = read_nic_dword(dev, RCR);
		write_nic_dword(dev, RCR,
			(tmpU4b|RCR_APPFCS|RCR_APP_ICV|RCR_APP_MIC));

		RT_TRACE(COMP_FIRMWARE, "FirmwareCheckReady(): Current RCR settings(%#x)\n", tmpU4b);


		// Set to normal mode.
		write_nic_byte(dev, LBKMD_SEL, LBK_NORMAL);

	}

	RT_TRACE(COMP_FIRMWARE, "<---FirmwareCheckReady(): LoadFWStatus(%d), rtStatus(%x)\n", LoadFWStatus, rtStatus);
	return (rtStatus == RT_STATUS_SUCCESS) ? true:false;
}