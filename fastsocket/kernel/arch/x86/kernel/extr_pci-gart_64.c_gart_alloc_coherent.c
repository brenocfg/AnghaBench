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
struct page {int dummy; } ;
struct device {int dummy; } ;
typedef  int gfp_t ;
typedef  scalar_t__ dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 int GFP_DMA ; 
 int __GFP_DMA ; 
 int __GFP_DMA32 ; 
 int __GFP_HIGHMEM ; 
 int __GFP_ZERO ; 
 int /*<<< orphan*/  __free_pages (struct page*,unsigned long) ; 
 struct page* alloc_pages (int,unsigned long) ; 
 scalar_t__ bad_dma_address ; 
 void* dma_generic_alloc_coherent (struct device*,size_t,scalar_t__*,int) ; 
 scalar_t__ dma_map_area (struct device*,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  flush_gart () ; 
 scalar_t__ force_iommu ; 
 unsigned long get_order (size_t) ; 
 void* page_address (struct page*) ; 
 int /*<<< orphan*/  page_to_phys (struct page*) ; 

__attribute__((used)) static void *
gart_alloc_coherent(struct device *dev, size_t size, dma_addr_t *dma_addr,
		    gfp_t flag)
{
	dma_addr_t paddr;
	unsigned long align_mask;
	struct page *page;

	if (force_iommu && !(flag & GFP_DMA)) {
		flag &= ~(__GFP_DMA | __GFP_HIGHMEM | __GFP_DMA32);
		page = alloc_pages(flag | __GFP_ZERO, get_order(size));
		if (!page)
			return NULL;

		align_mask = (1UL << get_order(size)) - 1;
		paddr = dma_map_area(dev, page_to_phys(page), size,
				     DMA_BIDIRECTIONAL, align_mask);

		flush_gart();
		if (paddr != bad_dma_address) {
			*dma_addr = paddr;
			return page_address(page);
		}
		__free_pages(page, get_order(size));
	} else
		return dma_generic_alloc_coherent(dev, size, dma_addr, flag);

	return NULL;
}