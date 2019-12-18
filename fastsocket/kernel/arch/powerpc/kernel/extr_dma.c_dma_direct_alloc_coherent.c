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
typedef  scalar_t__ dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  __GFP_HIGHMEM ; 
 void* __dma_alloc_coherent (struct device*,size_t,scalar_t__*,int /*<<< orphan*/ ) ; 
 struct page* alloc_pages_node (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dev_to_node (struct device*) ; 
 scalar_t__ get_dma_offset (struct device*) ; 
 int /*<<< orphan*/  get_order (size_t) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,size_t) ; 
 void* page_address (struct page*) ; 
 scalar_t__ virt_to_abs (void*) ; 

void *dma_direct_alloc_coherent(struct device *dev, size_t size,
				dma_addr_t *dma_handle, gfp_t flag)
{
	void *ret;
#ifdef CONFIG_NOT_COHERENT_CACHE
	ret = __dma_alloc_coherent(dev, size, dma_handle, flag);
	if (ret == NULL)
		return NULL;
	*dma_handle += get_dma_offset(dev);
	return ret;
#else
	struct page *page;
	int node = dev_to_node(dev);

	/* ignore region specifiers */
	flag  &= ~(__GFP_HIGHMEM);

	page = alloc_pages_node(node, flag, get_order(size));
	if (page == NULL)
		return NULL;
	ret = page_address(page);
	memset(ret, 0, size);
	*dma_handle = virt_to_abs(ret) + get_dma_offset(dev);

	return ret;
#endif
}