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
struct r8192_priv {int chan; scalar_t__ rf_chip; void* SwChnlInProgress; scalar_t__ SwChnlStep; scalar_t__ SwChnlStage; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_SCAN ; 
 void* FALSE ; 
 scalar_t__ RF_PSEUDO_11N ; 
 scalar_t__ RT_CANNOT_IO (struct net_device*) ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,char*,int) ; 
 void* TRUE ; 
 struct r8192_priv* ieee80211_priv (struct net_device*) ; 
 int /*<<< orphan*/  phy_FinishSwChnlNow (struct net_device*,int) ; 

void PHY_SwChnlPhy8192S(	// Only called during initialize
	struct net_device* dev,
	u8		channel
	)
{
	struct r8192_priv *priv = ieee80211_priv(dev);

	RT_TRACE(COMP_SCAN, "==>PHY_SwChnlPhy8192S(), switch to channel %d.\n", priv->chan);

#ifdef TO_DO_LIST
	// Cannot IO.
	if(RT_CANNOT_IO(dev))
		return;
#endif

	// Channel Switching is in progress.
	if(priv->SwChnlInProgress)
		return;

	//return immediately if it is peudo-phy
	if(priv->rf_chip == RF_PSEUDO_11N)
	{
		priv->SwChnlInProgress=FALSE;
		return;
	}

	priv->SwChnlInProgress = TRUE;
	if( channel == 0)
		channel = 1;

	priv->chan=channel;

	priv->SwChnlStage = 0;
	priv->SwChnlStep = 0;

	phy_FinishSwChnlNow(dev,channel);

	priv->SwChnlInProgress = FALSE;
}