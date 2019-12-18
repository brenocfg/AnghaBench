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
typedef  int /*<<< orphan*/  gfp_t ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 struct page* __dma_alloc (struct device*,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  page_to_phys (struct page*) ; 
 void* phys_to_uncached (int /*<<< orphan*/ ) ; 

void *dma_alloc_coherent(struct device *dev, size_t size,
			 dma_addr_t *handle, gfp_t gfp)
{
	struct page *page;
	void *ret = NULL;

	page = __dma_alloc(dev, size, handle, gfp);
	if (page)
		ret = phys_to_uncached(page_to_phys(page));

	return ret;
}