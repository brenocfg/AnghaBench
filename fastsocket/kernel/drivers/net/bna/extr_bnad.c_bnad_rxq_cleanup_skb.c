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
struct TYPE_5__ {scalar_t__ len; } ;
struct bnad_rx_unmap {TYPE_2__ vector; int /*<<< orphan*/ * skb; } ;
struct bnad {TYPE_1__* pcidev; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  dev_kfree_skb_any (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_addr ; 
 int /*<<< orphan*/  dma_unmap_addr (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_addr_set (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
bnad_rxq_cleanup_skb(struct bnad *bnad, struct bnad_rx_unmap *unmap)
{
	if (!unmap->skb)
		return;

	dma_unmap_single(&bnad->pcidev->dev,
			dma_unmap_addr(&unmap->vector, dma_addr),
			unmap->vector.len, DMA_FROM_DEVICE);
	dev_kfree_skb_any(unmap->skb);
	unmap->skb = NULL;
	dma_unmap_addr_set(&unmap->vector, dma_addr, 0);
	unmap->vector.len = 0;
}