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
struct sk_buff_head {int dummy; } ;
struct zd_mac {scalar_t__ ack_pending; int /*<<< orphan*/  ack_signal; struct sk_buff_head ack_wait_queue; } ;
struct zd_ctrlset {int dummy; } ;
struct sk_buff {int dummy; } ;
struct ieee80211_tx_info {int flags; struct ieee80211_hw** rate_driver_data; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 struct ieee80211_tx_info* IEEE80211_SKB_CB (struct sk_buff*) ; 
 int IEEE80211_TX_CTL_NO_ACK ; 
 scalar_t__ ZD_MAC_MAX_ACK_WAITERS ; 
 int /*<<< orphan*/  ieee80211_tx_info_clear_status (struct ieee80211_tx_info*) ; 
 int /*<<< orphan*/  ieee80211_tx_status_irqsafe (struct ieee80211_hw*,struct sk_buff*) ; 
 int /*<<< orphan*/  skb_dequeue (struct sk_buff_head*) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 
 scalar_t__ skb_queue_len (struct sk_buff_head*) ; 
 int /*<<< orphan*/  skb_queue_tail (struct sk_buff_head*,struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 
 struct zd_mac* zd_hw_mac (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  zd_mac_tx_status (struct ieee80211_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void zd_mac_tx_to_dev(struct sk_buff *skb, int error)
{
	struct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	struct ieee80211_hw *hw = info->rate_driver_data[0];
	struct zd_mac *mac = zd_hw_mac(hw);

	ieee80211_tx_info_clear_status(info);

	skb_pull(skb, sizeof(struct zd_ctrlset));
	if (unlikely(error ||
	    (info->flags & IEEE80211_TX_CTL_NO_ACK))) {
		/*
		 * FIXME : do we need to fill in anything ?
		 */
		ieee80211_tx_status_irqsafe(hw, skb);
	} else {
		struct sk_buff_head *q = &mac->ack_wait_queue;

		skb_queue_tail(q, skb);
		while (skb_queue_len(q) > ZD_MAC_MAX_ACK_WAITERS) {
			zd_mac_tx_status(hw, skb_dequeue(q),
					 mac->ack_pending ? mac->ack_signal : 0,
					 NULL);
			mac->ack_pending = 0;
		}
	}
}