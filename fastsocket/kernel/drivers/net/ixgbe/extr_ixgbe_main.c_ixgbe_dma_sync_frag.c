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
struct skb_frag_struct {int /*<<< orphan*/  page_offset; } ;
struct sk_buff {int dummy; } ;
struct ixgbe_ring {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int page_released; scalar_t__ dma; } ;
struct TYPE_3__ {struct skb_frag_struct* frags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 TYPE_2__* IXGBE_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  dma_sync_single_range_for_cpu (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_page (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixgbe_rx_bufsz (struct ixgbe_ring*) ; 
 int /*<<< orphan*/  ixgbe_rx_pg_size (struct ixgbe_ring*) ; 
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void ixgbe_dma_sync_frag(struct ixgbe_ring *rx_ring,
				struct sk_buff *skb)
{
	/* if the page was released unmap it, else just sync our portion */
	if (unlikely(IXGBE_CB(skb)->page_released)) {
		dma_unmap_page(rx_ring->dev, IXGBE_CB(skb)->dma,
			       ixgbe_rx_pg_size(rx_ring), DMA_FROM_DEVICE);
		IXGBE_CB(skb)->page_released = false;
	} else {
		struct skb_frag_struct *frag = &skb_shinfo(skb)->frags[0];

		dma_sync_single_range_for_cpu(rx_ring->dev,
					      IXGBE_CB(skb)->dma,
					      frag->page_offset,
					      ixgbe_rx_bufsz(rx_ring),
					      DMA_FROM_DEVICE);
	}
	IXGBE_CB(skb)->dma = 0;
}