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
struct TYPE_2__ {scalar_t__ expires; } ;
struct r8180_priv {scalar_t__ eRFPowerState; TYPE_1__ SwAntennaDiversityTimer; scalar_t__ up; } ;
struct net_device {int dummy; } ;
typedef  scalar_t__ RT_RF_POWER_STATE ;

/* Variables and functions */
 int /*<<< orphan*/  ANTENNA_DIVERSITY_TIMER_PERIOD ; 
 scalar_t__ MSECS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SwAntennaDiversity (struct net_device*) ; 
 int /*<<< orphan*/  add_timer (TYPE_1__*) ; 
 scalar_t__ eRfOff ; 
 scalar_t__ eRfSleep ; 
 scalar_t__ ieee80211_priv (struct net_device*) ; 
 scalar_t__ jiffies ; 

void
SwAntennaDiversityTimerCallback(
	struct net_device *dev
	)
{
	struct r8180_priv *priv = (struct r8180_priv *)ieee80211_priv(dev);
	RT_RF_POWER_STATE rtState;

	//printk("+SwAntennaDiversityTimerCallback()\n");

	//
	// We do NOT need to switch antenna while RF is off.
	// 2007.05.09, added by Roger.
	//
	rtState = priv->eRFPowerState;
	do{
		if (rtState == eRfOff)
		{
//			printk("SwAntennaDiversityTimer - RF is OFF.\n");
			break;
		}
		else if (rtState == eRfSleep)
		{
			// Don't access BB/RF under Disable PLL situation.
			//RT_TRACE((COMP_RF|COMP_ANTENNA), DBG_LOUD, ("SwAntennaDiversityTimerCallback(): RF is Sleep => skip it\n"));
			break;
		}
		SwAntennaDiversity(dev);

	}while(false);

	if(priv->up)
	{
		priv->SwAntennaDiversityTimer.expires = jiffies + MSECS(ANTENNA_DIVERSITY_TIMER_PERIOD);
		add_timer(&priv->SwAntennaDiversityTimer);
	}

	//printk("-SwAntennaDiversityTimerCallback()\n");
}