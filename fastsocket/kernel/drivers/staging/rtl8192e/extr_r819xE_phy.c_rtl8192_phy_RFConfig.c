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
struct r8192_priv {int rf_chip; } ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  RT_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_ERR ; 
 int /*<<< orphan*/  PHY_RF8256_Config (struct net_device*) ; 
#define  RF_8225 131 
#define  RF_8256 130 
#define  RF_8258 129 
#define  RF_PSEUDO_11N 128 
 int /*<<< orphan*/  RT_STATUS_SUCCESS ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,char*) ; 
 struct r8192_priv* ieee80211_priv (struct net_device*) ; 

RT_STATUS rtl8192_phy_RFConfig(struct net_device* dev)
{
	struct r8192_priv *priv = ieee80211_priv(dev);
	RT_STATUS rtStatus = RT_STATUS_SUCCESS;
	switch(priv->rf_chip)
	{
		case RF_8225:
//			rtStatus = PHY_RF8225_Config(Adapter);
			break;
		case RF_8256:
			rtStatus = PHY_RF8256_Config(dev);
			break;

		case RF_8258:
			break;
		case RF_PSEUDO_11N:
		//rtStatus = PHY_RF8225_Config(Adapter);
		break;

		default:
			RT_TRACE(COMP_ERR, "error chip id\n");
			break;
	}
	return rtStatus;
}