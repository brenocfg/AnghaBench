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
struct sk_buff {int /*<<< orphan*/  len; scalar_t__ data; int /*<<< orphan*/  priority; } ;
struct r8180_priv {int /*<<< orphan*/  tx_lock; TYPE_1__* ieee80211; } ;
struct net_device {int dummy; } ;
struct ieee80211_hdr_3addr {short frame_ctl; } ;
struct TYPE_2__ {int iw_mode; scalar_t__ bHwRadioOff; } ;

/* Variables and functions */
 int AC2Q (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DMESGW (char*,int /*<<< orphan*/ ) ; 
 short IEEE80211_FCTL_MOREFRAGS ; 
 int /*<<< orphan*/  check_nic_enought_desc (struct net_device*,int) ; 
 int /*<<< orphan*/  get_curr_tx_free_desc (struct net_device*,int) ; 
 scalar_t__ ieee80211_priv (struct net_device*) ; 
 int /*<<< orphan*/  ieee80211_stop_queue (TYPE_1__*) ; 
 int ieeerate2rtlrate (int) ; 
 int /*<<< orphan*/  rtl8180_tx (struct net_device*,scalar_t__,int /*<<< orphan*/ ,int,short,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void rtl8180_hard_data_xmit(struct sk_buff *skb,struct net_device *dev, int
rate)
{
	struct r8180_priv *priv = (struct r8180_priv *)ieee80211_priv(dev);
	int mode;
	struct ieee80211_hdr_3addr  *h = (struct ieee80211_hdr_3addr  *) skb->data;
	short morefrag = (h->frame_ctl) & IEEE80211_FCTL_MOREFRAGS;
	unsigned long flags;
	int priority;

	mode = priv->ieee80211->iw_mode;

	rate = ieeerate2rtlrate(rate);
	/*
	* This function doesn't require lock because we make
	* sure it's called with the tx_lock already acquired.
	* this come from the kernel's hard_xmit callback (trought
	* the ieee stack, or from the try_wake_queue (again trought
	* the ieee stack.
	*/
	priority = AC2Q(skb->priority);
	spin_lock_irqsave(&priv->tx_lock,flags);

	if(priv->ieee80211->bHwRadioOff)
	{
		spin_unlock_irqrestore(&priv->tx_lock,flags);

		return;
	}

	if (!check_nic_enought_desc(dev, priority)){
		DMESGW("Error: no descriptor left by previous TX (avail %d) ",
			get_curr_tx_free_desc(dev, priority));
		ieee80211_stop_queue(priv->ieee80211);
	}
	rtl8180_tx(dev, skb->data, skb->len, priority, morefrag,0,rate);
	if (!check_nic_enought_desc(dev, priority))
		ieee80211_stop_queue(priv->ieee80211);

	spin_unlock_irqrestore(&priv->tx_lock,flags);
}