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
typedef  int u16 ;
struct efx_rx_queue {unsigned int ptr_mask; struct efx_nic* efx; } ;
struct efx_rx_buffer {int flags; unsigned int len; int /*<<< orphan*/  page_offset; } ;
struct efx_nic {TYPE_1__* type; int /*<<< orphan*/  net_dev; int /*<<< orphan*/  rx_scatter; } ;
struct efx_channel {unsigned int rx_pkt_n_frags; unsigned int rx_pkt_index; } ;
struct TYPE_2__ {scalar_t__ rx_buffer_hash_size; } ;

/* Variables and functions */
 unsigned int EFX_RX_MAX_FRAGS ; 
 int EFX_RX_PKT_CSUMMED ; 
 int EFX_RX_PKT_DISCARD ; 
 unsigned int EFX_RX_USR_BUF_SIZE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  efx_discard_rx_packet (struct efx_channel*,struct efx_rx_buffer*,unsigned int) ; 
 int /*<<< orphan*/  efx_recycle_rx_pages (struct efx_channel*,struct efx_rx_buffer*,unsigned int) ; 
 struct efx_rx_buffer* efx_rx_buf_next (struct efx_rx_queue*,struct efx_rx_buffer*) ; 
 int /*<<< orphan*/  efx_rx_buf_va (struct efx_rx_buffer*) ; 
 struct efx_rx_buffer* efx_rx_buffer (struct efx_rx_queue*,unsigned int) ; 
 int /*<<< orphan*/  efx_rx_flush_packet (struct efx_channel*) ; 
 int /*<<< orphan*/  efx_rx_packet__check_len (struct efx_rx_queue*,struct efx_rx_buffer*,unsigned int) ; 
 struct efx_channel* efx_rx_queue_channel (struct efx_rx_queue*) ; 
 int /*<<< orphan*/  efx_rx_queue_index (struct efx_rx_queue*) ; 
 int /*<<< orphan*/  efx_sync_rx_buffer (struct efx_nic*,struct efx_rx_buffer*,unsigned int) ; 
 int /*<<< orphan*/  netif_vdbg (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,unsigned int,unsigned int,unsigned int,char*,char*) ; 
 int /*<<< orphan*/  prefetch (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rx_status ; 
 scalar_t__ unlikely (int) ; 

void efx_rx_packet(struct efx_rx_queue *rx_queue, unsigned int index,
		   unsigned int n_frags, unsigned int len, u16 flags)
{
	struct efx_nic *efx = rx_queue->efx;
	struct efx_channel *channel = efx_rx_queue_channel(rx_queue);
	struct efx_rx_buffer *rx_buf;

	rx_buf = efx_rx_buffer(rx_queue, index);
	rx_buf->flags |= flags;

	/* Validate the number of fragments and completed length */
	if (n_frags == 1) {
		efx_rx_packet__check_len(rx_queue, rx_buf, len);
	} else if (unlikely(n_frags > EFX_RX_MAX_FRAGS) ||
		   unlikely(len <= (n_frags - 1) * EFX_RX_USR_BUF_SIZE) ||
		   unlikely(len > n_frags * EFX_RX_USR_BUF_SIZE) ||
		   unlikely(!efx->rx_scatter)) {
		/* If this isn't an explicit discard request, either
		 * the hardware or the driver is broken.
		 */
		WARN_ON(!(len == 0 && rx_buf->flags & EFX_RX_PKT_DISCARD));
		rx_buf->flags |= EFX_RX_PKT_DISCARD;
	}

	netif_vdbg(efx, rx_status, efx->net_dev,
		   "RX queue %d received ids %x-%x len %d %s%s\n",
		   efx_rx_queue_index(rx_queue), index,
		   (index + n_frags - 1) & rx_queue->ptr_mask, len,
		   (rx_buf->flags & EFX_RX_PKT_CSUMMED) ? " [SUMMED]" : "",
		   (rx_buf->flags & EFX_RX_PKT_DISCARD) ? " [DISCARD]" : "");

	/* Discard packet, if instructed to do so.  Process the
	 * previous receive first.
	 */
	if (unlikely(rx_buf->flags & EFX_RX_PKT_DISCARD)) {
		efx_rx_flush_packet(channel);
		efx_discard_rx_packet(channel, rx_buf, n_frags);
		return;
	}

	if (n_frags == 1)
		rx_buf->len = len;

	/* Release and/or sync the DMA mapping - assumes all RX buffers
	 * consumed in-order per RX queue.
	 */
	efx_sync_rx_buffer(efx, rx_buf, rx_buf->len);

	/* Prefetch nice and early so data will (hopefully) be in cache by
	 * the time we look at it.
	 */
	prefetch(efx_rx_buf_va(rx_buf));

	rx_buf->page_offset += efx->type->rx_buffer_hash_size;
	rx_buf->len -= efx->type->rx_buffer_hash_size;

	if (n_frags > 1) {
		/* Release/sync DMA mapping for additional fragments.
		 * Fix length for last fragment.
		 */
		unsigned int tail_frags = n_frags - 1;

		for (;;) {
			rx_buf = efx_rx_buf_next(rx_queue, rx_buf);
			if (--tail_frags == 0)
				break;
			efx_sync_rx_buffer(efx, rx_buf, EFX_RX_USR_BUF_SIZE);
		}
		rx_buf->len = len - (n_frags - 1) * EFX_RX_USR_BUF_SIZE;
		efx_sync_rx_buffer(efx, rx_buf, rx_buf->len);
	}

	/* All fragments have been DMA-synced, so recycle pages. */
	rx_buf = efx_rx_buffer(rx_queue, index);
	efx_recycle_rx_pages(channel, rx_buf, n_frags);

	/* Pipeline receives so that we give time for packet headers to be
	 * prefetched into cache.
	 */
	efx_rx_flush_packet(channel);
	channel->rx_pkt_n_frags = n_frags;
	channel->rx_pkt_index = index;
}