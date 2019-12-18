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
struct r8180_priv {scalar_t__ eRFPowerState; scalar_t__ RfOffReason; int /*<<< orphan*/  eInactivePowerState; int /*<<< orphan*/  bSwRfProcessing; scalar_t__ bInactivePs; } ;
struct net_device {int dummy; } ;
typedef  scalar_t__ RT_RF_POWER_STATE ;

/* Variables and functions */
 int /*<<< orphan*/  InactivePowerSave (struct net_device*) ; 
 scalar_t__ RF_CHANGE_BY_IPS ; 
 scalar_t__ eRfOff ; 
 int /*<<< orphan*/  eRfOn ; 
 scalar_t__ eRfSleep ; 
 scalar_t__ ieee80211_priv (struct net_device*) ; 

void
IPSLeave(
	struct net_device *dev
	)
{
	struct r8180_priv *priv = (struct r8180_priv *)ieee80211_priv(dev);
	RT_RF_POWER_STATE rtState;
	//printk("===================================>leave IPS\n");
	if (priv->bInactivePs)
	{
		rtState = priv->eRFPowerState;
		if ((rtState == eRfOff || rtState == eRfSleep) && (!priv->bSwRfProcessing) && priv->RfOffReason <= RF_CHANGE_BY_IPS)
		{
//			printk("IPSLeave(): Turn on RF.\n");
			priv->eInactivePowerState = eRfOn;
			InactivePowerSave(dev);
		}
	}
//	printk("priv->eRFPowerState is %d\n",priv->eRFPowerState);
}