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
struct b44 {int flags; int rx_pending; int /*<<< orphan*/  tx_ring_dma; TYPE_1__* sdev; int /*<<< orphan*/  rx_ring_dma; int /*<<< orphan*/  tx_ring; int /*<<< orphan*/  rx_ring; } ;
struct TYPE_2__ {int /*<<< orphan*/  dma_dev; } ;

/* Variables and functions */
 int B44_FLAG_RX_RING_HACK ; 
 int B44_FLAG_TX_RING_HACK ; 
 int /*<<< orphan*/  B44_RX_RING_BYTES ; 
 int /*<<< orphan*/  B44_TX_RING_BYTES ; 
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 int /*<<< orphan*/  DMA_TABLE_BYTES ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 scalar_t__ b44_alloc_rx_skb (struct b44*,int,int) ; 
 int /*<<< orphan*/  b44_free_rings (struct b44*) ; 
 int /*<<< orphan*/  dma_sync_single_for_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void b44_init_rings(struct b44 *bp)
{
	int i;

	b44_free_rings(bp);

	memset(bp->rx_ring, 0, B44_RX_RING_BYTES);
	memset(bp->tx_ring, 0, B44_TX_RING_BYTES);

	if (bp->flags & B44_FLAG_RX_RING_HACK)
		dma_sync_single_for_device(bp->sdev->dma_dev, bp->rx_ring_dma,
					   DMA_TABLE_BYTES, DMA_BIDIRECTIONAL);

	if (bp->flags & B44_FLAG_TX_RING_HACK)
		dma_sync_single_for_device(bp->sdev->dma_dev, bp->tx_ring_dma,
					   DMA_TABLE_BYTES, DMA_TO_DEVICE);

	for (i = 0; i < bp->rx_pending; i++) {
		if (b44_alloc_rx_skb(bp, -1, i) < 0)
			break;
	}
}