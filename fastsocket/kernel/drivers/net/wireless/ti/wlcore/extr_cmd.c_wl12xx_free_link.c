#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
struct TYPE_3__ {size_t bcast_hlid; } ;
struct wl12xx_vif {scalar_t__ bss_type; scalar_t__ total_freed_pkts; TYPE_1__ ap; int /*<<< orphan*/  links_map; } ;
struct wl1271 {scalar_t__ active_link_count; TYPE_2__* links; int /*<<< orphan*/  flags; int /*<<< orphan*/  wl_lock; int /*<<< orphan*/  links_map; } ;
struct TYPE_4__ {scalar_t__ total_freed_pkts; int /*<<< orphan*/ * wlvif; int /*<<< orphan*/  addr; scalar_t__ ba_bitmap; scalar_t__ prev_freed_pkts; scalar_t__ allocated_pkts; } ;

/* Variables and functions */
 scalar_t__ BSS_TYPE_AP_BSS ; 
 scalar_t__ BSS_TYPE_STA_BSS ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  WL1271_FLAG_RECOVERY_IN_PROGRESS ; 
 scalar_t__ WL1271_TX_SQN_POST_RECOVERY_PADDING ; 
 size_t WL12XX_INVALID_LINK_ID ; 
 int /*<<< orphan*/  __clear_bit (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wl1271_tx_reset_link_queues (struct wl1271*,size_t) ; 

void wl12xx_free_link(struct wl1271 *wl, struct wl12xx_vif *wlvif, u8 *hlid)
{
	unsigned long flags;

	if (*hlid == WL12XX_INVALID_LINK_ID)
		return;

	/* these bits are used by op_tx */
	spin_lock_irqsave(&wl->wl_lock, flags);
	__clear_bit(*hlid, wl->links_map);
	__clear_bit(*hlid, wlvif->links_map);
	spin_unlock_irqrestore(&wl->wl_lock, flags);

	wl->links[*hlid].allocated_pkts = 0;
	wl->links[*hlid].prev_freed_pkts = 0;
	wl->links[*hlid].ba_bitmap = 0;
	memset(wl->links[*hlid].addr, 0, ETH_ALEN);

	/*
	 * At this point op_tx() will not add more packets to the queues. We
	 * can purge them.
	 */
	wl1271_tx_reset_link_queues(wl, *hlid);
	wl->links[*hlid].wlvif = NULL;

	if (wlvif->bss_type == BSS_TYPE_STA_BSS ||
	    (wlvif->bss_type == BSS_TYPE_AP_BSS &&
	     *hlid == wlvif->ap.bcast_hlid)) {
		/*
		 * save the total freed packets in the wlvif, in case this is
		 * recovery or suspend
		 */
		wlvif->total_freed_pkts = wl->links[*hlid].total_freed_pkts;

		/*
		 * increment the initial seq number on recovery to account for
		 * transmitted packets that we haven't yet got in the FW status
		 */
		if (test_bit(WL1271_FLAG_RECOVERY_IN_PROGRESS, &wl->flags))
			wlvif->total_freed_pkts +=
					WL1271_TX_SQN_POST_RECOVERY_PADDING;
	}

	wl->links[*hlid].total_freed_pkts = 0;

	*hlid = WL12XX_INVALID_LINK_ID;
	wl->active_link_count--;
	WARN_ON_ONCE(wl->active_link_count < 0);
}