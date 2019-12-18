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
typedef  size_t u8 ;
struct wl12xx_vif {size_t last_tx_hlid; int /*<<< orphan*/ * tx_queue_count; } ;
struct wl1271 {int /*<<< orphan*/  wl_lock; int /*<<< orphan*/ * tx_queue_count; TYPE_1__* links; int /*<<< orphan*/  flags; } ;
struct sk_buff {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * tx_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  WL1271_FLAG_DUMMY_PACKET_PENDING ; 
 size_t WL12XX_MAX_LINKS ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_get_queue_mapping (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_queue_head (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int wl1271_tx_get_queue (int /*<<< orphan*/ ) ; 
 scalar_t__ wl12xx_is_dummy_packet (struct wl1271*,struct sk_buff*) ; 

__attribute__((used)) static void wl1271_skb_queue_head(struct wl1271 *wl, struct wl12xx_vif *wlvif,
				  struct sk_buff *skb, u8 hlid)
{
	unsigned long flags;
	int q = wl1271_tx_get_queue(skb_get_queue_mapping(skb));

	if (wl12xx_is_dummy_packet(wl, skb)) {
		set_bit(WL1271_FLAG_DUMMY_PACKET_PENDING, &wl->flags);
	} else {
		skb_queue_head(&wl->links[hlid].tx_queue[q], skb);

		/* make sure we dequeue the same packet next time */
		wlvif->last_tx_hlid = (hlid + WL12XX_MAX_LINKS - 1) %
				      WL12XX_MAX_LINKS;
	}

	spin_lock_irqsave(&wl->wl_lock, flags);
	wl->tx_queue_count[q]++;
	if (wlvif)
		wlvif->tx_queue_count[q]++;
	spin_unlock_irqrestore(&wl->wl_lock, flags);
}