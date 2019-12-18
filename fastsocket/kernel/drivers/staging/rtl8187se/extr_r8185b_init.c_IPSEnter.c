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
struct r8180_priv {scalar_t__ eRFPowerState; int /*<<< orphan*/  eInactivePowerState; TYPE_1__* ieee80211; int /*<<< orphan*/  bSwRfProcessing; scalar_t__ bInactivePs; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {scalar_t__ state; } ;
typedef  scalar_t__ RT_RF_POWER_STATE ;

/* Variables and functions */
 scalar_t__ IEEE80211_LINKED ; 
 int /*<<< orphan*/  InactivePowerSave (struct net_device*) ; 
 int /*<<< orphan*/  eRfOff ; 
 scalar_t__ eRfOn ; 
 scalar_t__ ieee80211_priv (struct net_device*) ; 

void
IPSEnter(
	struct net_device *dev
	)
{
	struct r8180_priv *priv = (struct r8180_priv *)ieee80211_priv(dev);
	RT_RF_POWER_STATE rtState;
	//printk("==============================>enter IPS\n");
	if (priv->bInactivePs)
	{
		rtState = priv->eRFPowerState;

		//
		// Added by Bruce, 2007-12-25.
		// Do not enter IPS in the following conditions:
		// (1) RF is already OFF or Sleep
		// (2) bSwRfProcessing (indicates the IPS is still under going)
		// (3) Connectted (only disconnected can trigger IPS)
		// (4) IBSS (send Beacon)
		// (5) AP mode (send Beacon)
		//
		if (rtState == eRfOn && !priv->bSwRfProcessing
			&& (priv->ieee80211->state != IEEE80211_LINKED ))
		{
	//		printk("IPSEnter(): Turn off RF.\n");
			priv->eInactivePowerState = eRfOff;
			InactivePowerSave(dev);
		}
	}
//	printk("priv->eRFPowerState is %d\n",priv->eRFPowerState);
}