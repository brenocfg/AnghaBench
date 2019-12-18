#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct ieee80211_network {int dummy; } ;
struct TYPE_5__ {scalar_t__ expires; } ;
struct TYPE_4__ {int /*<<< orphan*/  tx_auth_rq; } ;
struct ieee80211_device {TYPE_2__ associate_timer; int /*<<< orphan*/  state; TYPE_1__ softmac_stats; struct ieee80211_network current_network; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  IEEE80211_ASSOCIATING_AUTHENTICATING ; 
 int /*<<< orphan*/  IEEE80211_DEBUG_MGMT (char*) ; 
 int /*<<< orphan*/  add_timer (TYPE_2__*) ; 
 int /*<<< orphan*/  ieee80211_associate_abort (struct ieee80211_device*) ; 
 struct sk_buff* ieee80211_authentication_req (struct ieee80211_network*,struct ieee80211_device*,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  softmac_mgmt_xmit (struct sk_buff*,struct ieee80211_device*) ; 
 int /*<<< orphan*/  timer_pending (TYPE_2__*) ; 

void ieee80211_associate_step1(struct ieee80211_device *ieee)
{
	struct ieee80211_network *beacon = &ieee->current_network;
	struct sk_buff *skb;

	IEEE80211_DEBUG_MGMT("Stopping scan\n");

	ieee->softmac_stats.tx_auth_rq++;
	skb=ieee80211_authentication_req(beacon, ieee, 0);

	if (!skb)
		ieee80211_associate_abort(ieee);
	else{
		ieee->state = IEEE80211_ASSOCIATING_AUTHENTICATING ;
		IEEE80211_DEBUG_MGMT("Sending authentication request\n");
		//printk(KERN_WARNING "Sending authentication request\n");
		softmac_mgmt_xmit(skb, ieee);
		//BUGON when you try to add_timer twice, using mod_timer may be better, john0709
		if(!timer_pending(&ieee->associate_timer)){
			ieee->associate_timer.expires = jiffies + (HZ / 2);
			add_timer(&ieee->associate_timer);
		}
		//dev_kfree_skb_any(skb);//edit by thomas
	}
}