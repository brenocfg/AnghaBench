#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ expires; } ;
struct r8180_priv {scalar_t__ ForcedDataRate; TYPE_2__ rateadapter_timer; int /*<<< orphan*/  RateAdaptivePeriod; TYPE_1__* ieee80211; int /*<<< orphan*/  up; } ;
struct net_device {int dummy; } ;
struct TYPE_3__ {scalar_t__ iw_mode; scalar_t__ state; int /*<<< orphan*/  rate_adapter_wq; int /*<<< orphan*/  wq; } ;

/* Variables and functions */
 scalar_t__ IEEE80211_LINKED ; 
 scalar_t__ IW_MODE_MASTER ; 
 scalar_t__ MSECS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_timer (TYPE_2__*) ; 
 struct r8180_priv* ieee80211_priv (struct net_device*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,void*) ; 

void timer_rate_adaptive(unsigned long data)
{
	struct r8180_priv* priv = ieee80211_priv((struct net_device *)data);
	//DMESG("---->timer_rate_adaptive()\n");
	if(!priv->up)
	{
//		DMESG("<----timer_rate_adaptive():driver is not up!\n");
		return;
	}
	if((priv->ieee80211->iw_mode != IW_MODE_MASTER)
			&& (priv->ieee80211->state == IEEE80211_LINKED) &&
			(priv->ForcedDataRate == 0) )
	{
//	DMESG("timer_rate_adaptive():schedule rate_adapter_wq\n");
		queue_work(priv->ieee80211->wq, (void *)&priv->ieee80211->rate_adapter_wq);
//		StaRateAdaptive87SE((struct net_device *)data);
	}
	priv->rateadapter_timer.expires = jiffies + MSECS(priv->RateAdaptivePeriod);
	add_timer(&priv->rateadapter_timer);
	//DMESG("<----timer_rate_adaptive()\n");
}