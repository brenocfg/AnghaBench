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
struct wl1271 {int /*<<< orphan*/  hw; int /*<<< orphan*/  deferred_tx_queue; int /*<<< orphan*/  deferred_rx_queue; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ieee80211_rx_ni (int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  ieee80211_tx_status_ni (int /*<<< orphan*/ ,struct sk_buff*) ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void wl1271_flush_deferred_work(struct wl1271 *wl)
{
	struct sk_buff *skb;

	/* Pass all received frames to the network stack */
	while ((skb = skb_dequeue(&wl->deferred_rx_queue)))
		ieee80211_rx_ni(wl->hw, skb);

	/* Return sent skbs to the network stack */
	while ((skb = skb_dequeue(&wl->deferred_tx_queue)))
		ieee80211_tx_status_ni(wl->hw, skb);
}