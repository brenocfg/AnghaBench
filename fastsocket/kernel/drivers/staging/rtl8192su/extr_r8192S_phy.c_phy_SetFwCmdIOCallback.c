#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct r8192_priv {int CurrentFwCmdIO; int SetFwCmdInProgress; int /*<<< orphan*/  rf_type; TYPE_2__* ieee80211; int /*<<< orphan*/  up; } ;
struct net_device {int dummy; } ;
struct TYPE_4__ {TYPE_1__* pHTInfo; } ;
struct TYPE_3__ {int IOTAction; int IOTRaFunc; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_CMD ; 
 int /*<<< orphan*/  ChkFwCmdIoDone (struct net_device*) ; 
#define  FW_CMD_DIG_DISABLE 142 
#define  FW_CMD_DIG_ENABLE 141 
#define  FW_CMD_DIG_HALT 140 
#define  FW_CMD_DIG_RESUME 139 
#define  FW_CMD_HIGH_PWR_DISABLE 138 
#define  FW_CMD_HIGH_PWR_ENABLE 137 
#define  FW_CMD_IQK_ENABLE 136 
#define  FW_CMD_PAUSE_DM_BY_SCAN 135 
#define  FW_CMD_RA_ACTIVE 134 
#define  FW_CMD_RA_REFRESH_BG 133 
#define  FW_CMD_RA_REFRESH_N 132 
#define  FW_CMD_RA_RESET 131 
#define  FW_CMD_RESUME_DM_BY_SCAN 130 
#define  FW_CMD_TXPWR_TRACK_DISABLE 129 
#define  FW_CMD_TXPWR_TRACK_ENABLE 128 
 int FW_DIG_DISABLE ; 
 int FW_DIG_ENABLE ; 
 int FW_DIG_HALT ; 
 int FW_DIG_RESUME ; 
 int FW_HIGH_PWR_DISABLE ; 
 int FW_HIGH_PWR_ENABLE ; 
 int FW_IQK_ENABLE ; 
 int FW_RA_ACTIVE ; 
 int FW_RA_ENABLE_BG ; 
 int FW_RA_REFRESH ; 
 int FW_RA_RESET ; 
 int FW_TXPWR_TRACK_DISABLE ; 
 int FW_TXPWR_TRACK_ENABLE ; 
 int HT_IOT_ACT_DISABLE_HIGH_POWER ; 
 int HT_IOT_RAFUNC_DISABLE_ALL ; 
 int /*<<< orphan*/  RF_1T2R ; 
 int /*<<< orphan*/  RF_2T2R ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  WFM5 ; 
 int bMaskByte0 ; 
 int bMaskByte2 ; 
 int bMaskDWord ; 
 struct r8192_priv* ieee80211_priv (struct net_device*) ; 
 int /*<<< orphan*/  rCCK0_CCA ; 
 int /*<<< orphan*/  rOFDM0_RxDetector1 ; 
 int /*<<< orphan*/  rOFDM0_TRMuxPar ; 
 int /*<<< orphan*/  rOFDM0_XAAGCCore1 ; 
 int /*<<< orphan*/  rOFDM0_XBAGCCore1 ; 
 int /*<<< orphan*/  rOFDM1_TRxPathEnable ; 
 int rtl8192_QueryBBReg (struct net_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtl8192_setBBreg (struct net_device*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  write_nic_dword (struct net_device*,int /*<<< orphan*/ ,int) ; 

void phy_SetFwCmdIOCallback(struct net_device* dev)
{
	//struct net_device* dev = (struct net_device*) data;
	u32 	 	input;
	static u32 ScanRegister;
	struct r8192_priv *priv = ieee80211_priv(dev);
	if(!priv->up)
	{
		RT_TRACE(COMP_CMD, "SetFwCmdIOTimerCallback(): driver is going to unload\n");
		return;
	}

	RT_TRACE(COMP_CMD, "--->SetFwCmdIOTimerCallback(): Cmd(%#x), SetFwCmdInProgress(%d)\n", priv->CurrentFwCmdIO, priv->SetFwCmdInProgress);

	switch(priv->CurrentFwCmdIO)
	{
		case FW_CMD_HIGH_PWR_ENABLE:
			if((priv->ieee80211->pHTInfo->IOTAction & HT_IOT_ACT_DISABLE_HIGH_POWER)==0)
				write_nic_dword(dev, WFM5, FW_HIGH_PWR_ENABLE);
			break;

		case FW_CMD_HIGH_PWR_DISABLE:
			write_nic_dword(dev, WFM5, FW_HIGH_PWR_DISABLE);
			break;

		case FW_CMD_DIG_RESUME:
			write_nic_dword(dev, WFM5, FW_DIG_RESUME);
			break;

		case FW_CMD_DIG_HALT:
			write_nic_dword(dev, WFM5, FW_DIG_HALT);
			break;

		//
		// <Roger_Notes> The following FW CMD IO was combined into single operation
		// (i.e., to prevent number of system workitem out of resource!!).
		// 2008.12.04.
		//
		case FW_CMD_RESUME_DM_BY_SCAN:
			RT_TRACE(COMP_CMD, "[FW CMD] Set HIGHPWR enable and DIG resume!!\n");
			if((priv->ieee80211->pHTInfo->IOTAction & HT_IOT_ACT_DISABLE_HIGH_POWER)==0)
			{
				write_nic_dword(dev, WFM5, FW_HIGH_PWR_ENABLE); //break;
				ChkFwCmdIoDone(dev);
			}
			write_nic_dword(dev, WFM5, FW_DIG_RESUME);
			break;

		case FW_CMD_PAUSE_DM_BY_SCAN:
			RT_TRACE(COMP_CMD, "[FW CMD] Set HIGHPWR disable and DIG halt!!\n");
			write_nic_dword(dev, WFM5, FW_HIGH_PWR_DISABLE); //break;
			ChkFwCmdIoDone(dev);
			write_nic_dword(dev, WFM5, FW_DIG_HALT);
			break;

		//
		// <Roger_Notes> The following FW CMD IO should be checked
		// (i.e., workitem schedule timing issue!!).
		// 2008.12.04.
		//
		case FW_CMD_DIG_DISABLE:
			RT_TRACE(COMP_CMD, "[FW CMD] Set DIG disable!!\n");
			write_nic_dword(dev, WFM5, FW_DIG_DISABLE);
			break;

		case FW_CMD_DIG_ENABLE:
			RT_TRACE(COMP_CMD, "[FW CMD] Set DIG enable!!\n");
			write_nic_dword(dev, WFM5, FW_DIG_ENABLE);
			break;

		case FW_CMD_RA_RESET:
			write_nic_dword(dev, WFM5, FW_RA_RESET);
			break;

		case FW_CMD_RA_ACTIVE:
			write_nic_dword(dev, WFM5, FW_RA_ACTIVE);
			break;

		case FW_CMD_RA_REFRESH_N:
			RT_TRACE(COMP_CMD, "[FW CMD] Set RA refresh!! N\n");
			if(priv->ieee80211->pHTInfo->IOTRaFunc & HT_IOT_RAFUNC_DISABLE_ALL)
				input = FW_RA_REFRESH;
			else
				input = FW_RA_REFRESH | (priv->ieee80211->pHTInfo->IOTRaFunc << 8);
			write_nic_dword(dev, WFM5, input);
			break;
		case FW_CMD_RA_REFRESH_BG:
			RT_TRACE(COMP_CMD, "[FW CMD] Set RA refresh!! B/G\n");
			write_nic_dword(dev, WFM5, FW_RA_REFRESH);
			ChkFwCmdIoDone(dev);
			write_nic_dword(dev, WFM5, FW_RA_ENABLE_BG);
			break;

		case FW_CMD_IQK_ENABLE:
			write_nic_dword(dev, WFM5, FW_IQK_ENABLE);
			break;

		case FW_CMD_TXPWR_TRACK_ENABLE:
			write_nic_dword(dev, WFM5, FW_TXPWR_TRACK_ENABLE);
			break;

		case FW_CMD_TXPWR_TRACK_DISABLE:
			write_nic_dword(dev, WFM5, FW_TXPWR_TRACK_DISABLE);
			break;

		default:
			RT_TRACE(COMP_CMD,"Unknown FW Cmd IO(%#x)\n", priv->CurrentFwCmdIO);
			break;
	}

	ChkFwCmdIoDone(dev);

	switch(priv->CurrentFwCmdIO)
	{
		case FW_CMD_HIGH_PWR_DISABLE:
			//if(pMgntInfo->bTurboScan)
			{
				//Lower initial gain
				rtl8192_setBBreg(dev, rOFDM0_XAAGCCore1, bMaskByte0, 0x17);
				rtl8192_setBBreg(dev, rOFDM0_XBAGCCore1, bMaskByte0, 0x17);
				// CCA threshold
				rtl8192_setBBreg(dev, rCCK0_CCA, bMaskByte2, 0x40);
				// Disable OFDM Part
				rtl8192_setBBreg(dev, rOFDM0_TRMuxPar, bMaskByte2, 0x1);
				ScanRegister = rtl8192_QueryBBReg(dev, rOFDM0_RxDetector1,bMaskDWord);
				rtl8192_setBBreg(dev, rOFDM0_RxDetector1, 0xf, 0xf);
				rtl8192_setBBreg(dev, rOFDM1_TRxPathEnable, 0xf, 0x0);
			}
			break;

		case FW_CMD_HIGH_PWR_ENABLE:
			//if(pMgntInfo->bTurboScan)
			{
				rtl8192_setBBreg(dev, rOFDM0_XAAGCCore1, bMaskByte0, 0x36);
				rtl8192_setBBreg(dev, rOFDM0_XBAGCCore1, bMaskByte0, 0x36);

				// CCA threshold
				rtl8192_setBBreg(dev, rCCK0_CCA, bMaskByte2, 0x83);
				// Enable OFDM Part
				rtl8192_setBBreg(dev, rOFDM0_TRMuxPar, bMaskByte2, 0x0);

				//LZM ADD because sometimes there is no FW_CMD_HIGH_PWR_DISABLE, this value will be 0.
				if(ScanRegister != 0){
				rtl8192_setBBreg(dev, rOFDM0_RxDetector1, bMaskDWord, ScanRegister);
				}

				if(priv->rf_type == RF_1T2R || priv->rf_type == RF_2T2R)
					rtl8192_setBBreg(dev, rOFDM1_TRxPathEnable, 0xf, 0x3);
				else
					rtl8192_setBBreg(dev, rOFDM1_TRxPathEnable, 0xf, 0x1);
			}
			break;
	}

	priv->SetFwCmdInProgress = false;// Clear FW CMD operation flag.
	RT_TRACE(COMP_CMD, "<---SetFwCmdIOWorkItemCallback()\n");

}