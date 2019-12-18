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
struct device {int* coherent_dma_mask; } ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  scalar_t__ dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_DMA ; 
 int PAGE_SHIFT ; 
 unsigned long __get_free_pages (int /*<<< orphan*/ ,int) ; 
 unsigned long __pa (unsigned long) ; 
 int /*<<< orphan*/  flush_kernel_dcache_range (unsigned long,size_t) ; 
 int get_order (size_t) ; 
 int /*<<< orphan*/  gfp ; 
 int /*<<< orphan*/  map_uncached_pages (unsigned long,size_t,unsigned long) ; 
 unsigned long pcxl_alloc_range (size_t) ; 

__attribute__((used)) static void * pa11_dma_alloc_consistent (struct device *dev, size_t size, dma_addr_t *dma_handle, gfp_t flag)
{
	unsigned long vaddr;
	unsigned long paddr;
	int order;

	order = get_order(size);
	size = 1 << (order + PAGE_SHIFT);
	vaddr = pcxl_alloc_range(size);
	paddr = __get_free_pages(flag, order);
	flush_kernel_dcache_range(paddr, size);
	paddr = __pa(paddr);
	map_uncached_pages(vaddr, size, paddr);
	*dma_handle = (dma_addr_t) paddr;

#if 0
/* This probably isn't needed to support EISA cards.
** ISA cards will certainly only support 24-bit DMA addressing.
** Not clear if we can, want, or need to support ISA.
*/
	if (!dev || *dev->coherent_dma_mask < 0xffffffff)
		gfp |= GFP_DMA;
#endif
	return (void *)vaddr;
}