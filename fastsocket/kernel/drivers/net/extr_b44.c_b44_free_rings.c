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
struct ring_info {TYPE_2__* skb; int /*<<< orphan*/  mapping; } ;
struct b44 {TYPE_1__* sdev; struct ring_info* tx_buffers; struct ring_info* rx_buffers; } ;
struct TYPE_4__ {int /*<<< orphan*/  len; } ;
struct TYPE_3__ {int /*<<< orphan*/  dma_dev; } ;

/* Variables and functions */
 int B44_RX_RING_SIZE ; 
 int B44_TX_RING_SIZE ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  RX_PKT_BUF_SZ ; 
 int /*<<< orphan*/  dev_kfree_skb_any (TYPE_2__*) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void b44_free_rings(struct b44 *bp)
{
	struct ring_info *rp;
	int i;

	for (i = 0; i < B44_RX_RING_SIZE; i++) {
		rp = &bp->rx_buffers[i];

		if (rp->skb == NULL)
			continue;
		dma_unmap_single(bp->sdev->dma_dev, rp->mapping, RX_PKT_BUF_SZ,
				 DMA_FROM_DEVICE);
		dev_kfree_skb_any(rp->skb);
		rp->skb = NULL;
	}

	/* XXX needs changes once NETIF_F_SG is set... */
	for (i = 0; i < B44_TX_RING_SIZE; i++) {
		rp = &bp->tx_buffers[i];

		if (rp->skb == NULL)
			continue;
		dma_unmap_single(bp->sdev->dma_dev, rp->mapping, rp->skb->len,
				 DMA_TO_DEVICE);
		dev_kfree_skb_any(rp->skb);
		rp->skb = NULL;
	}
}