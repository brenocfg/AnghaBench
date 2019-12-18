#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_9__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {TYPE_2__* rates; } ;
struct ieee80211_tx_info {TYPE_3__ status; int /*<<< orphan*/  flags; } ;
struct TYPE_14__ {int /*<<< orphan*/  last_tx; } ;
struct b43legacy_wldev {TYPE_9__* wl; TYPE_4__ stats; } ;
struct b43legacy_txstatus {scalar_t__ rts_count; int frame_count; scalar_t__ acked; int /*<<< orphan*/  cookie; } ;
struct b43legacy_txhdr_fw3 {int dummy; } ;
struct b43legacy_dmaring {int current_slot; int used_slots; int nr_slots; int stopped; size_t queue_prio; int /*<<< orphan*/  index; int /*<<< orphan*/  tx; } ;
struct b43legacy_dmadesc_meta {scalar_t__ is_last_fragment; TYPE_7__* skb; int /*<<< orphan*/  dmaaddr; } ;
struct TYPE_17__ {int /*<<< orphan*/  tx_work; TYPE_5__* hw; scalar_t__* tx_queue_stopped; } ;
struct TYPE_16__ {int len; } ;
struct TYPE_11__ {scalar_t__ short_frame_max_tx_count; } ;
struct TYPE_15__ {TYPE_1__ conf; } ;
struct TYPE_12__ {int count; int idx; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43legacy_DBG_DMAVERBOSE ; 
 int /*<<< orphan*/  B43legacy_WARN_ON (int) ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 struct ieee80211_tx_info* IEEE80211_SKB_CB (TYPE_7__*) ; 
 int /*<<< orphan*/  IEEE80211_TX_STAT_ACK ; 
 scalar_t__ SLOTS_PER_PACKET ; 
 scalar_t__ b43legacy_debug (struct b43legacy_wldev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43legacydbg (TYPE_9__*,char*,int /*<<< orphan*/ ,...) ; 
 scalar_t__ free_slots (struct b43legacy_dmaring*) ; 
 int /*<<< orphan*/  ieee80211_queue_work (TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee80211_tx_info_clear_status (struct ieee80211_tx_info*) ; 
 int /*<<< orphan*/  ieee80211_tx_status_irqsafe (TYPE_5__*,TYPE_7__*) ; 
 int /*<<< orphan*/  ieee80211_wake_queue (TYPE_5__*,size_t) ; 
 int /*<<< orphan*/  jiffies ; 
 int next_slot (struct b43legacy_dmaring*,int) ; 
 int /*<<< orphan*/  op32_idx2desc (struct b43legacy_dmaring*,int,struct b43legacy_dmadesc_meta**) ; 
 struct b43legacy_dmaring* parse_cookie (struct b43legacy_wldev*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  unmap_descbuffer (struct b43legacy_dmaring*,int /*<<< orphan*/ ,int,int) ; 

void b43legacy_dma_handle_txstatus(struct b43legacy_wldev *dev,
				 const struct b43legacy_txstatus *status)
{
	struct b43legacy_dmaring *ring;
	struct b43legacy_dmadesc_meta *meta;
	int retry_limit;
	int slot;
	int firstused;

	ring = parse_cookie(dev, status->cookie, &slot);
	if (unlikely(!ring))
		return;
	B43legacy_WARN_ON(!ring->tx);

	/* Sanity check: TX packets are processed in-order on one ring.
	 * Check if the slot deduced from the cookie really is the first
	 * used slot. */
	firstused = ring->current_slot - ring->used_slots + 1;
	if (firstused < 0)
		firstused = ring->nr_slots + firstused;
	if (unlikely(slot != firstused)) {
		/* This possibly is a firmware bug and will result in
		 * malfunction, memory leaks and/or stall of DMA functionality.
		 */
		b43legacydbg(dev->wl, "Out of order TX status report on DMA "
			     "ring %d. Expected %d, but got %d\n",
			     ring->index, firstused, slot);
		return;
	}

	while (1) {
		B43legacy_WARN_ON(!(slot >= 0 && slot < ring->nr_slots));
		op32_idx2desc(ring, slot, &meta);

		if (meta->skb)
			unmap_descbuffer(ring, meta->dmaaddr,
					 meta->skb->len, 1);
		else
			unmap_descbuffer(ring, meta->dmaaddr,
					 sizeof(struct b43legacy_txhdr_fw3),
					 1);

		if (meta->is_last_fragment) {
			struct ieee80211_tx_info *info;
			BUG_ON(!meta->skb);
			info = IEEE80211_SKB_CB(meta->skb);

			/* preserve the confiured retry limit before clearing the status
			 * The xmit function has overwritten the rc's value with the actual
			 * retry limit done by the hardware */
			retry_limit = info->status.rates[0].count;
			ieee80211_tx_info_clear_status(info);

			if (status->acked)
				info->flags |= IEEE80211_TX_STAT_ACK;

			if (status->rts_count > dev->wl->hw->conf.short_frame_max_tx_count) {
				/*
				 * If the short retries (RTS, not data frame) have exceeded
				 * the limit, the hw will not have tried the selected rate,
				 * but will have used the fallback rate instead.
				 * Don't let the rate control count attempts for the selected
				 * rate in this case, otherwise the statistics will be off.
				 */
				info->status.rates[0].count = 0;
				info->status.rates[1].count = status->frame_count;
			} else {
				if (status->frame_count > retry_limit) {
					info->status.rates[0].count = retry_limit;
					info->status.rates[1].count = status->frame_count -
							retry_limit;

				} else {
					info->status.rates[0].count = status->frame_count;
					info->status.rates[1].idx = -1;
				}
			}

			/* Call back to inform the ieee80211 subsystem about the
			 * status of the transmission.
			 * Some fields of txstat are already filled in dma_tx().
			 */
			ieee80211_tx_status_irqsafe(dev->wl->hw, meta->skb);
			/* skb is freed by ieee80211_tx_status_irqsafe() */
			meta->skb = NULL;
		} else {
			/* No need to call free_descriptor_buffer here, as
			 * this is only the txhdr, which is not allocated.
			 */
			B43legacy_WARN_ON(meta->skb != NULL);
		}

		/* Everything unmapped and free'd. So it's not used anymore. */
		ring->used_slots--;

		if (meta->is_last_fragment)
			break;
		slot = next_slot(ring, slot);
	}
	dev->stats.last_tx = jiffies;
	if (ring->stopped) {
		B43legacy_WARN_ON(free_slots(ring) < SLOTS_PER_PACKET);
		ring->stopped = false;
	}

	if (dev->wl->tx_queue_stopped[ring->queue_prio]) {
		dev->wl->tx_queue_stopped[ring->queue_prio] = 0;
	} else {
		/* If the driver queue is running wake the corresponding
		 * mac80211 queue. */
		ieee80211_wake_queue(dev->wl->hw, ring->queue_prio);
		if (b43legacy_debug(dev, B43legacy_DBG_DMAVERBOSE))
			b43legacydbg(dev->wl, "Woke up TX ring %d\n",
				     ring->index);
	}
	/* Add work to the queue. */
	ieee80211_queue_work(dev->wl->hw, &dev->wl->tx_work);
}