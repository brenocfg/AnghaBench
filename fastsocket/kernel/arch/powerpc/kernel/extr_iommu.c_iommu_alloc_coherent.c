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
struct iommu_table {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  scalar_t__ dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 scalar_t__ DMA_ERROR_CODE ; 
 unsigned int IOMAP_MAX_ORDER ; 
 size_t IOMMU_PAGE_SHIFT ; 
 size_t PAGE_ALIGN (size_t) ; 
 struct page* alloc_pages_node (int,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  free_pages (unsigned long,unsigned int) ; 
 unsigned int get_iommu_order (size_t) ; 
 unsigned int get_order (size_t) ; 
 scalar_t__ iommu_alloc (struct device*,struct iommu_table*,void*,unsigned int,int /*<<< orphan*/ ,unsigned long,unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,size_t) ; 
 void* page_address (struct page*) ; 
 int /*<<< orphan*/  printk (char*,size_t) ; 

void *iommu_alloc_coherent(struct device *dev, struct iommu_table *tbl,
			   size_t size,	dma_addr_t *dma_handle,
			   unsigned long mask, gfp_t flag, int node)
{
	void *ret = NULL;
	dma_addr_t mapping;
	unsigned int order;
	unsigned int nio_pages, io_order;
	struct page *page;

	size = PAGE_ALIGN(size);
	order = get_order(size);

 	/*
	 * Client asked for way too much space.  This is checked later
	 * anyway.  It is easier to debug here for the drivers than in
	 * the tce tables.
	 */
	if (order >= IOMAP_MAX_ORDER) {
		printk("iommu_alloc_consistent size too large: 0x%lx\n", size);
		return NULL;
	}

	if (!tbl)
		return NULL;

	/* Alloc enough pages (and possibly more) */
	page = alloc_pages_node(node, flag, order);
	if (!page)
		return NULL;
	ret = page_address(page);
	memset(ret, 0, size);

	/* Set up tces to cover the allocated range */
	nio_pages = size >> IOMMU_PAGE_SHIFT;
	io_order = get_iommu_order(size);
	mapping = iommu_alloc(dev, tbl, ret, nio_pages, DMA_BIDIRECTIONAL,
			      mask >> IOMMU_PAGE_SHIFT, io_order, NULL);
	if (mapping == DMA_ERROR_CODE) {
		free_pages((unsigned long)ret, order);
		return NULL;
	}
	*dma_handle = mapping;
	return ret;
}