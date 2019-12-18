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
typedef  size_t u8 ;
typedef  int u32 ;
struct r8192_priv {size_t NumTotalRFPath; TYPE_1__* PHYRegDef; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  rfintfs; int /*<<< orphan*/  rfHSSIPara2; int /*<<< orphan*/  rfintfo; int /*<<< orphan*/  rfintfe; } ;
typedef  int /*<<< orphan*/  RF90_RADIO_PATH_E ;
typedef  TYPE_1__ BB_REGISTER_DEFINITION_T ;

/* Variables and functions */
#define  RF90_PATH_A 131 
#define  RF90_PATH_B 130 
#define  RF90_PATH_C 129 
#define  RF90_PATH_D 128 
 int b3WireAddressLength ; 
 int b3WireDataLength ; 
 int bRFSI_RFENV ; 
 struct r8192_priv* ieee80211_priv (struct net_device*) ; 
 int rtl8192_QueryBBReg (struct net_device*,int /*<<< orphan*/ ,int) ; 
 int rtl8192_phy_ConfigRFWithHeaderFile (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl8192_setBBreg (struct net_device*,int /*<<< orphan*/ ,int,int) ; 

bool phy_RF8225_Config_ParaFile(struct net_device* dev)
{
	u32					u4RegValue = 0;
	//static char				szRadioAFile[] = RTL819X_PHY_RADIO_A;
	//static char				szRadioBFile[] = RTL819X_PHY_RADIO_B;
	u8					eRFPath;
	bool				rtStatus = true;
	struct r8192_priv *priv = ieee80211_priv(dev);
	BB_REGISTER_DEFINITION_T	*pPhyReg;
	//u8						eCheckItem;

#if	1
	//3//-----------------------------------------------------------------
	//3// <2> Initialize RF
	//3//-----------------------------------------------------------------
	//for(eRFPath = RF90_PATH_A; eRFPath <pHalData->NumTotalRFPath; eRFPath++)
	for(eRFPath = 0; eRFPath <priv->NumTotalRFPath; eRFPath++)
	{

		pPhyReg = &priv->PHYRegDef[eRFPath];

		/*----Store original RFENV control type----*/
		switch(eRFPath)
		{
		case RF90_PATH_A:
		case RF90_PATH_C:
			u4RegValue = rtl8192_QueryBBReg(dev, pPhyReg->rfintfs, bRFSI_RFENV);
			break;
		case RF90_PATH_B :
		case RF90_PATH_D:
			u4RegValue = rtl8192_QueryBBReg(dev, pPhyReg->rfintfs, bRFSI_RFENV<<16);
			break;
		}

		/*----Set RF_ENV enable----*/
		rtl8192_setBBreg(dev, pPhyReg->rfintfe, bRFSI_RFENV<<16, 0x1);

		/*----Set RF_ENV output high----*/
		rtl8192_setBBreg(dev, pPhyReg->rfintfo, bRFSI_RFENV, 0x1);

		/* Set bit number of Address and Data for RF register */
		rtl8192_setBBreg(dev, pPhyReg->rfHSSIPara2, b3WireAddressLength, 0x0); 	// Set 1 to 4 bits for 8255
		rtl8192_setBBreg(dev, pPhyReg->rfHSSIPara2, b3WireDataLength, 0x0);	// Set 0 to 12  bits for 8255


		/*----Initialize RF fom connfiguration file----*/
		switch(eRFPath)
		{
		case RF90_PATH_A:
			//rtStatus = PHY_ConfigRFWithParaFile(dev, (char* )&szRadioAFile, (RF90_RADIO_PATH_E)eRFPath);
			rtStatus = rtl8192_phy_ConfigRFWithHeaderFile(dev,(RF90_RADIO_PATH_E)eRFPath);
			break;
		case RF90_PATH_B:
			//rtStatus = PHY_ConfigRFWithParaFile(dev, (char* )&szRadioBFile, (RF90_RADIO_PATH_E)eRFPath);
			rtStatus = rtl8192_phy_ConfigRFWithHeaderFile(dev,(RF90_RADIO_PATH_E)eRFPath);
			break;
		case RF90_PATH_C:
			break;
		case RF90_PATH_D:
			break;
		}

		/*----Restore RFENV control type----*/;
		switch(eRFPath)
		{
		case RF90_PATH_A:
		case RF90_PATH_C:
			rtl8192_setBBreg(dev, pPhyReg->rfintfs, bRFSI_RFENV, u4RegValue);
			break;
		case RF90_PATH_B :
		case RF90_PATH_D:
			rtl8192_setBBreg(dev, pPhyReg->rfintfs, bRFSI_RFENV<<16, u4RegValue);
			break;
		}

		if(rtStatus == false){
			//RT_TRACE(COMP_FPGA, DBG_LOUD, ("phy_RF8225_Config_ParaFile():Radio[%d] Fail!!", eRFPath));
			goto phy_RF8225_Config_ParaFile_Fail;
		}

	}

	//RT_TRACE(COMP_INIT, DBG_LOUD, ("<---phy_RF8225_Config_ParaFile()\n"));
	return rtStatus;

phy_RF8225_Config_ParaFile_Fail:
#endif
	return rtStatus;
}