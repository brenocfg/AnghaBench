#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct TYPE_6__ {scalar_t__ expires; } ;
struct TYPE_5__ {scalar_t__ beacon_interval; } ;
struct TYPE_4__ {int /*<<< orphan*/  tx_beacons; } ;
struct ieee80211_device {TYPE_3__ beacon_timer; scalar_t__ beacon_txing; TYPE_2__ current_network; TYPE_1__ softmac_stats; } ;

/* Variables and functions */
 scalar_t__ MSECS (scalar_t__) ; 
 int /*<<< orphan*/  add_timer (TYPE_3__*) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 struct sk_buff* ieee80211_get_beacon_ (struct ieee80211_device*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  softmac_mgmt_xmit (struct sk_buff*,struct ieee80211_device*) ; 

void ieee80211_send_beacon(struct ieee80211_device *ieee)
{
	struct sk_buff *skb;

	//unsigned long flags;

	skb = ieee80211_get_beacon_(ieee);

	if (skb){
		softmac_mgmt_xmit(skb, ieee);
		ieee->softmac_stats.tx_beacons++;
		dev_kfree_skb_any(skb);//edit by thomas
	}

	//printk(KERN_WARNING "[1] beacon sending!\n");
	ieee->beacon_timer.expires = jiffies +
		(MSECS( ieee->current_network.beacon_interval -5));

	//spin_lock_irqsave(&ieee->beacon_lock,flags);
	if(ieee->beacon_txing)
		add_timer(&ieee->beacon_timer);
	//spin_unlock_irqrestore(&ieee->beacon_lock,flags);
}