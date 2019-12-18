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
struct r8180_priv {int up; TYPE_1__* ieee80211; scalar_t__ bSwAntennaDiverity; scalar_t__ bInactivePs; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {scalar_t__ iw_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMESG (char*) ; 
 int /*<<< orphan*/  IPSLeave (struct net_device*) ; 
 scalar_t__ IW_MODE_ADHOC ; 
 int /*<<< orphan*/  SwAntennaDiversityTimerCallback (struct net_device*) ; 
 struct r8180_priv* ieee80211_priv (struct net_device*) ; 
 int /*<<< orphan*/  ieee80211_softmac_start_protocol (TYPE_1__*) ; 
 int /*<<< orphan*/  rtl8185b_adapter_start (struct net_device*) ; 
 int /*<<< orphan*/  rtl8185b_rx_enable (struct net_device*) ; 
 int /*<<< orphan*/  rtl8185b_tx_enable (struct net_device*) ; 
 int /*<<< orphan*/  timer_rate_adaptive (unsigned long) ; 
 int /*<<< orphan*/  watch_dog_adaptive (unsigned long) ; 

int _rtl8180_up(struct net_device *dev)
{
	struct r8180_priv *priv = ieee80211_priv(dev);

	priv->up=1;

	DMESG("Bringing up iface");
	rtl8185b_adapter_start(dev);
	rtl8185b_rx_enable(dev);
	rtl8185b_tx_enable(dev);
	if(priv->bInactivePs){
		if(priv->ieee80211->iw_mode == IW_MODE_ADHOC)
			IPSLeave(dev);
	}
#ifdef RATE_ADAPT
       timer_rate_adaptive((unsigned long)dev);
#endif
	watch_dog_adaptive((unsigned long)dev);
#ifdef SW_ANTE
        if(priv->bSwAntennaDiverity)
			SwAntennaDiversityTimerCallback(dev);
#endif
	ieee80211_softmac_start_protocol(priv->ieee80211);

	return 0;
}