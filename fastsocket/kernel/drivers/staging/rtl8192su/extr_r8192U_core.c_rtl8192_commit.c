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
struct r8192_priv {scalar_t__ up; int /*<<< orphan*/  ieee80211; int /*<<< orphan*/  watch_dog_timer; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int _rtl8192_up (struct net_device*) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 struct r8192_priv* ieee80211_priv (struct net_device*) ; 
 int /*<<< orphan*/  ieee80211_softmac_stop_protocol (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl8192_cancel_deferred_work (struct r8192_priv*) ; 
 int /*<<< orphan*/  rtl8192_rtx_disable (struct net_device*) ; 

void rtl8192_commit(struct net_device *dev)
{
	struct r8192_priv *priv = ieee80211_priv(dev);
	int reset_status = 0;
	//u8 reset_times = 0;
	if (priv->up == 0) return ;
	priv->up = 0;

	rtl8192_cancel_deferred_work(priv);
	del_timer_sync(&priv->watch_dog_timer);
	//cancel_delayed_work(&priv->SwChnlWorkItem);

	ieee80211_softmac_stop_protocol(priv->ieee80211);

	//rtl8192_irq_disable(dev);
	rtl8192_rtx_disable(dev);
	reset_status = _rtl8192_up(dev);

}