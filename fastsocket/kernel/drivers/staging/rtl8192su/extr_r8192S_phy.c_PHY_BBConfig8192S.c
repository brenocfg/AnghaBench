#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u8 ;
struct r8192_priv {int rf_pathmap; scalar_t__ rf_type; } ;
struct net_device {int dummy; } ;
typedef  scalar_t__ RT_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_INIT ; 
 scalar_t__ RF_1T1R ; 
 scalar_t__ RF_1T2R ; 
 scalar_t__ RF_2T2R ; 
 scalar_t__ RF_2T2R_GREEN ; 
 scalar_t__ RF_2T4R ; 
 scalar_t__ RT_STATUS_SUCCESS ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,char*,scalar_t__,int) ; 
 struct r8192_priv* ieee80211_priv (struct net_device*) ; 
 scalar_t__ phy_BB8192S_Config_ParaFile (struct net_device*) ; 
 int /*<<< orphan*/  phy_InitBBRFRegisterDefinition (struct net_device*) ; 
 int /*<<< orphan*/  rFPGA0_TxInfo ; 
 int /*<<< orphan*/  rOFDM0_TRxPathEnable ; 
 int rtl8192_QueryBBReg (struct net_device*,int /*<<< orphan*/ ,int) ; 

extern	bool
PHY_BBConfig8192S(struct net_device* dev)
{
	RT_STATUS	rtStatus = RT_STATUS_SUCCESS;

	u8 PathMap = 0, index = 0, rf_num = 0;
	struct r8192_priv 	*priv = ieee80211_priv(dev);
	phy_InitBBRFRegisterDefinition(dev);

	//
	// Config BB and AGC
	//
	//switch( Adapter->MgntInfo.bRegHwParaFile )
	//{
	//	case 0:
	//		phy_BB8190_Config_HardCode(dev);
	//		break;

	//	case 1:
			rtStatus = phy_BB8192S_Config_ParaFile(dev);
	//		break;

	//	case 2:
			// Partial Modify.
	//		phy_BB8190_Config_HardCode(dev);
	//		phy_BB8192S_Config_ParaFile(dev);
	//		break;

	//	default:
	//		phy_BB8190_Config_HardCode(dev);
	//		break;
	//}
	PathMap = (u8)(rtl8192_QueryBBReg(dev, rFPGA0_TxInfo, 0xf) |
				rtl8192_QueryBBReg(dev, rOFDM0_TRxPathEnable, 0xf));
	priv->rf_pathmap = PathMap;
	for(index = 0; index<4; index++)
	{
		if((PathMap>>index)&0x1)
			rf_num++;
	}

	if((priv->rf_type==RF_1T1R && rf_num!=1) ||
		(priv->rf_type==RF_1T2R && rf_num!=2) ||
		(priv->rf_type==RF_2T2R && rf_num!=2) ||
		(priv->rf_type==RF_2T2R_GREEN && rf_num!=2) ||
		(priv->rf_type==RF_2T4R && rf_num!=4))
	{
		RT_TRACE( COMP_INIT, "PHY_BBConfig8192S: RF_Type(%x) does not match RF_Num(%x)!!\n", priv->rf_type, rf_num);
	}
	return (rtStatus == RT_STATUS_SUCCESS) ? 1:0;
}