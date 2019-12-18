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
struct r8192_priv {scalar_t__ rf_type; int NumTotalRFPath; } ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  RT_STATUS ;

/* Variables and functions */
 scalar_t__ RF_1T1R ; 
 int /*<<< orphan*/  RT_STATUS_SUCCESS ; 
 struct r8192_priv* ieee80211_priv (struct net_device*) ; 
 int /*<<< orphan*/  phy_RF6052_Config_ParaFile (struct net_device*) ; 

RT_STATUS PHY_RF6052_Config(struct net_device* dev)
{
	struct r8192_priv 			*priv = ieee80211_priv(dev);
	RT_STATUS				rtStatus = RT_STATUS_SUCCESS;
	//RF90_RADIO_PATH_E		eRFPath;
	//BB_REGISTER_DEFINITION_T	*pPhyReg;
	//u32						OrgStoreRFIntSW[RF90_PATH_D+1];

	//
	// Initialize general global value
	//
	// TODO: Extend RF_PATH_C and RF_PATH_D in the future
	if(priv->rf_type == RF_1T1R)
		priv->NumTotalRFPath = 1;
	else
		priv->NumTotalRFPath = 2;

	//
	// Config BB and RF
	//
//	switch( priv->bRegHwParaFile )
//	{
//		case 0:
//			phy_RF6052_Config_HardCode(dev);
//			break;

//		case 1:
			rtStatus = phy_RF6052_Config_ParaFile(dev);
//			break;

//		case 2:
			// Partial Modify.
//			phy_RF6052_Config_HardCode(dev);
//			phy_RF6052_Config_ParaFile(dev);
//			break;

//		default:
//			phy_RF6052_Config_HardCode(dev);
//			break;
//	}
	return rtStatus;

}