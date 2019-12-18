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
struct sk_buff {int len; size_t queue_mapping; } ;
struct ieee80211_tx_control {int dummy; } ;
struct ieee80211_hw {int dummy; } ;
struct b43_wl {int /*<<< orphan*/  hw; int /*<<< orphan*/  tx_work; int /*<<< orphan*/ * tx_queue_stopped; int /*<<< orphan*/ * tx_queue; } ;
struct TYPE_2__ {int /*<<< orphan*/  nr_frags; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43_WARN_ON (int /*<<< orphan*/ ) ; 
 struct b43_wl* hw_to_b43_wl (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  ieee80211_free_txskb (struct ieee80211_hw*,struct sk_buff*) ; 
 int /*<<< orphan*/  ieee80211_queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee80211_stop_queue (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void b43_op_tx(struct ieee80211_hw *hw,
		      struct ieee80211_tx_control *control,
		      struct sk_buff *skb)
{
	struct b43_wl *wl = hw_to_b43_wl(hw);

	if (unlikely(skb->len < 2 + 2 + 6)) {
		/* Too short, this can't be a valid frame. */
		ieee80211_free_txskb(hw, skb);
		return;
	}
	B43_WARN_ON(skb_shinfo(skb)->nr_frags);

	skb_queue_tail(&wl->tx_queue[skb->queue_mapping], skb);
	if (!wl->tx_queue_stopped[skb->queue_mapping]) {
		ieee80211_queue_work(wl->hw, &wl->tx_work);
	} else {
		ieee80211_stop_queue(wl->hw, skb->queue_mapping);
	}
}