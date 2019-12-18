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
struct page {int dummy; } ;
struct ixgbe_rx_buffer {int dma; scalar_t__ page_offset; struct page* page; } ;
struct TYPE_2__ {int /*<<< orphan*/  alloc_rx_page_failed; } ;
struct ixgbe_ring {TYPE_1__ rx_stats; int /*<<< orphan*/  dev; } ;
typedef  int dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int GFP_ATOMIC ; 
 int __GFP_COLD ; 
 int __GFP_COMP ; 
 int /*<<< orphan*/  __free_pages (struct page*,int /*<<< orphan*/ ) ; 
 struct page* alloc_pages (int,int /*<<< orphan*/ ) ; 
 int dma_map_page (int /*<<< orphan*/ ,struct page*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ixgbe_rx_pg_order (struct ixgbe_ring*) ; 
 int /*<<< orphan*/  ixgbe_rx_pg_size (struct ixgbe_ring*) ; 
 scalar_t__ likely (int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static bool ixgbe_alloc_mapped_page(struct ixgbe_ring *rx_ring,
				    struct ixgbe_rx_buffer *bi)
{
	struct page *page = bi->page;
	dma_addr_t dma = bi->dma;

	/* since we are recycling buffers we should seldom need to alloc */
	if (likely(dma))
		return true;

	/* alloc new page for storage */
	if (likely(!page)) {
		page = alloc_pages(GFP_ATOMIC | __GFP_COLD | __GFP_COMP,
				   ixgbe_rx_pg_order(rx_ring));
		if (unlikely(!page)) {
			rx_ring->rx_stats.alloc_rx_page_failed++;
			return false;
		}
		bi->page = page;
	}

	/* map page for use */
	dma = dma_map_page(rx_ring->dev, page, 0,
			   ixgbe_rx_pg_size(rx_ring), DMA_FROM_DEVICE);

	/*
	 * if mapping failed free memory back to system since
	 * there isn't much point in holding memory we can't use
	 */
	if (dma_mapping_error(rx_ring->dev, dma)) {
		__free_pages(page, ixgbe_rx_pg_order(rx_ring));
		bi->page = NULL;

		rx_ring->rx_stats.alloc_rx_page_failed++;
		return false;
	}

	bi->dma = dma;
	bi->page_offset = 0;

	return true;
}