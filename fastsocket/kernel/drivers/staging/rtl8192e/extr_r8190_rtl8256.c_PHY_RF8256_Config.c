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
struct r8192_priv {int /*<<< orphan*/  NumTotalRFPath; } ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  RT_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  RTL819X_TOTAL_RF_PATH ; 
 int /*<<< orphan*/  RT_STATUS_SUCCESS ; 
 struct r8192_priv* ieee80211_priv (struct net_device*) ; 
 int /*<<< orphan*/  phy_RF8256_Config_ParaFile (struct net_device*) ; 

RT_STATUS PHY_RF8256_Config(struct net_device* dev)
{
	struct r8192_priv *priv = ieee80211_priv(dev);
	// Initialize general global value
	//
	RT_STATUS rtStatus = RT_STATUS_SUCCESS;
	// TODO: Extend RF_PATH_C and RF_PATH_D in the future
	priv->NumTotalRFPath = RTL819X_TOTAL_RF_PATH;
	// Config BB and RF
	rtStatus = phy_RF8256_Config_ParaFile(dev);

	return rtStatus;
}