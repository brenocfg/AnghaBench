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
struct device {int* dma_mask; } ;
typedef  int gfp_t ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int GFP_DMA ; 
 int __GFP_DMA ; 
 int __GFP_HIGHMEM ; 
 scalar_t__ __get_free_pages (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_order (size_t) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  virt_to_phys (void*) ; 

void *dma_alloc_coherent(struct device *dev, size_t size,
			   dma_addr_t *dma_handle, gfp_t gfp)
{
	void *ret;
	/* ignore region specifiers */
	gfp &= ~(__GFP_DMA | __GFP_HIGHMEM);

	if (dev == NULL || (*dev->dma_mask < 0xffffffff))
		gfp |= GFP_DMA;
	ret = (void *)__get_free_pages(gfp, get_order(size));

	if (ret != NULL) {
		memset(ret, 0, size);
		*dma_handle = virt_to_phys(ret);
	}
	return ret;
}