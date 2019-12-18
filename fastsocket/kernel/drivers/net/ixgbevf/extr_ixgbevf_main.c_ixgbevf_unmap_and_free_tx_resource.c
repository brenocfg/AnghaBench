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
struct ixgbevf_tx_buffer {scalar_t__ time_stamp; int /*<<< orphan*/ * skb; scalar_t__ dma; int /*<<< orphan*/  length; scalar_t__ mapped_as_page; } ;
struct ixgbevf_ring {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  dev_kfree_skb_any (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_unmap_page (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ixgbevf_unmap_and_free_tx_resource(struct ixgbevf_ring *tx_ring,
					       struct ixgbevf_tx_buffer
					       *tx_buffer_info)
{
	if (tx_buffer_info->dma) {
		if (tx_buffer_info->mapped_as_page)
			dma_unmap_page(tx_ring->dev,
				       tx_buffer_info->dma,
				       tx_buffer_info->length,
				       DMA_TO_DEVICE);
		else
			dma_unmap_single(tx_ring->dev,
					 tx_buffer_info->dma,
					 tx_buffer_info->length,
					 DMA_TO_DEVICE);
		tx_buffer_info->dma = 0;
	}
	if (tx_buffer_info->skb) {
		dev_kfree_skb_any(tx_buffer_info->skb);
		tx_buffer_info->skb = NULL;
	}
	tx_buffer_info->time_stamp = 0;
	/* tx_buffer_info must be completely set up in the transmit path */
}