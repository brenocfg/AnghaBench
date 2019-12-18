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
struct device {int coherent_dma_mask; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int GFP_DMA ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int __GFP_DMA ; 
 int __GFP_HIGHMEM ; 
 unsigned long __get_free_pages (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_order (size_t) ; 
 int /*<<< orphan*/  memset (void*,int,size_t) ; 
 int /*<<< orphan*/  mn10300_dcache_flush_inv_range2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virt_to_bus (void*) ; 
 int /*<<< orphan*/  virt_to_phys (void*) ; 

void *dma_alloc_coherent(struct device *dev, size_t size,
			 dma_addr_t *dma_handle, int gfp)
{
	unsigned long addr;
	void *ret;

	/* ignore region specifiers */
	gfp &= ~(__GFP_DMA | __GFP_HIGHMEM);

	if (dev == NULL || dev->coherent_dma_mask < 0xffffffff)
		gfp |= GFP_DMA;

	addr = __get_free_pages(gfp, get_order(size));
	if (!addr)
		return NULL;

	/* map the coherent memory through the uncached memory window */
	ret = (void *) (addr | 0x20000000);

	/* fill the memory with obvious rubbish */
	memset((void *) addr, 0xfb, size);

	/* write back and evict all cache lines covering this region */
	mn10300_dcache_flush_inv_range2(virt_to_phys((void *) addr), PAGE_SIZE);

	*dma_handle = virt_to_bus((void *) addr);
	return ret;
}