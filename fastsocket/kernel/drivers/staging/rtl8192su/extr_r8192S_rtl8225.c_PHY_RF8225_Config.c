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
struct r8192_priv {int NumTotalRFPath; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 struct r8192_priv* ieee80211_priv (struct net_device*) ; 
 int /*<<< orphan*/  phy_RF8225_Config_HardCode (struct net_device*) ; 
 int /*<<< orphan*/  phy_RF8225_Config_ParaFile (struct net_device*) ; 

bool PHY_RF8225_Config(struct net_device* dev )
{
	struct r8192_priv *priv = ieee80211_priv(dev);
	bool	rtStatus = true;
	//RF90_RADIO_PATH_E			eRFPath;
	//BB_REGISTER_DEFINITION_T	*pPhyReg;
	//u32						OrgStoreRFIntSW[RF90_PATH_D+1];

	//
	// Initialize general global value
	//
	// TODO: Extend RF_PATH_C and RF_PATH_D in the future
	priv->NumTotalRFPath = 2;

	//
	// Config BB and RF
	//
	//switch( Adapter->MgntInfo.bRegHwParaFile )
	//{
	//	case 0:
	//		phy_RF8225_Config_HardCode(dev);
	//		break;

	//	case 1:
	//		rtStatus = phy_RF8225_Config_ParaFile(dev);
	//		break;

	//	case 2:
			// Partial Modify.
			phy_RF8225_Config_HardCode(dev);
			phy_RF8225_Config_ParaFile(dev);
	//		break;

	//	default:
	//		phy_RF8225_Config_HardCode(dev);
	//		break;
	//}
	return rtStatus;

}