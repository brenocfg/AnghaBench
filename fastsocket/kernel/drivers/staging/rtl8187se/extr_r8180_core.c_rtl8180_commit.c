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
struct r8180_priv {scalar_t__ up; TYPE_1__* ieee80211; int /*<<< orphan*/  SwAntennaDiversityTimer; int /*<<< orphan*/  rateadapter_timer; int /*<<< orphan*/  watch_dog_timer; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  tx_pw_wq; int /*<<< orphan*/  hw_dig_wq; int /*<<< orphan*/  hw_sleep_wq; int /*<<< orphan*/  hw_wakeup_wq; int /*<<< orphan*/  rate_adapter_wq; } ;

/* Variables and functions */
 int /*<<< orphan*/  _rtl8180_up (struct net_device*) ; 
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 struct r8180_priv* ieee80211_priv (struct net_device*) ; 
 int /*<<< orphan*/  ieee80211_softmac_stop_protocol (TYPE_1__*) ; 
 int /*<<< orphan*/  rtl8180_irq_disable (struct net_device*) ; 
 int /*<<< orphan*/  rtl8180_rtx_disable (struct net_device*) ; 

void rtl8180_commit(struct net_device *dev)
{
	struct r8180_priv *priv = ieee80211_priv(dev);

	if (priv->up == 0)
		return ;

	del_timer_sync(&priv->watch_dog_timer);
	del_timer_sync(&priv->rateadapter_timer);
	cancel_delayed_work(&priv->ieee80211->rate_adapter_wq);
	cancel_delayed_work(&priv->ieee80211->hw_wakeup_wq);
	cancel_delayed_work(&priv->ieee80211->hw_sleep_wq);
	cancel_delayed_work(&priv->ieee80211->hw_dig_wq);
	cancel_delayed_work(&priv->ieee80211->tx_pw_wq);
	del_timer_sync(&priv->SwAntennaDiversityTimer);
	ieee80211_softmac_stop_protocol(priv->ieee80211);
	rtl8180_irq_disable(dev);
	rtl8180_rtx_disable(dev);
	_rtl8180_up(dev);
}