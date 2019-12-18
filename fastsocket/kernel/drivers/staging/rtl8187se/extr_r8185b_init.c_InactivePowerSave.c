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
struct r8180_priv {int bSwRfProcessing; int /*<<< orphan*/  eInactivePowerState; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MgntActSet_RF_State (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RF_CHANGE_BY_IPS ; 
 scalar_t__ ieee80211_priv (struct net_device*) ; 

void
InactivePowerSave(
	struct net_device *dev
	)
{
	struct r8180_priv *priv = (struct r8180_priv *)ieee80211_priv(dev);
	//u8 index = 0;

	//
	// This flag "bSwRfProcessing", indicates the status of IPS procedure, should be set if the IPS workitem
	// is really scheduled.
	// The old code, sets this flag before scheduling the IPS workitem and however, at the same time the
	// previous IPS workitem did not end yet, fails to schedule the current workitem. Thus, bSwRfProcessing
	// blocks the IPS procedure of switching RF.
	// By Bruce, 2007-12-25.
	//
	priv->bSwRfProcessing = true;

	MgntActSet_RF_State(dev, priv->eInactivePowerState, RF_CHANGE_BY_IPS);

	//
	// To solve CAM values miss in RF OFF, rewrite CAM values after RF ON. By Bruce, 2007-09-20.
	//

	priv->bSwRfProcessing = false;
}