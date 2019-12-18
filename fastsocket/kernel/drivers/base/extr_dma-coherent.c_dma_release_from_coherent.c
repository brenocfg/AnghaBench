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
struct dma_coherent_mem {void* virt_base; int size; int /*<<< orphan*/  bitmap; } ;
struct device {struct dma_coherent_mem* dma_mem; } ;

/* Variables and functions */
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  bitmap_release_region (int /*<<< orphan*/ ,int,int) ; 

int dma_release_from_coherent(struct device *dev, int order, void *vaddr)
{
	struct dma_coherent_mem *mem = dev ? dev->dma_mem : NULL;

	if (mem && vaddr >= mem->virt_base && vaddr <
		   (mem->virt_base + (mem->size << PAGE_SHIFT))) {
		int page = (vaddr - mem->virt_base) >> PAGE_SHIFT;

		bitmap_release_region(mem->bitmap, page, order);
		return 1;
	}
	return 0;
}