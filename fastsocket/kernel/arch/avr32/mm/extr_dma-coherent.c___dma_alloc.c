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
 size_t PAGE_ALIGN (size_t) ; 
 size_t PAGE_SHIFT ; 
 int /*<<< orphan*/  __GFP_COMP ; 
 int /*<<< orphan*/  __free_page (struct page*) ; 
 struct page* alloc_pages (int /*<<< orphan*/ ,int) ; 
 int get_order (size_t) ; 
 int /*<<< orphan*/  invalidate_dcache_region (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  page_to_bus (struct page*) ; 
 int /*<<< orphan*/  page_to_phys (struct page*) ; 
 int /*<<< orphan*/  phys_to_virt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  split_page (struct page*,int) ; 

__attribute__((used)) static struct page *__dma_alloc(struct device *dev, size_t size,
				dma_addr_t *handle, gfp_t gfp)
{
	struct page *page, *free, *end;
	int order;

	/* Following is a work-around (a.k.a. hack) to prevent pages
	 * with __GFP_COMP being passed to split_page() which cannot
	 * handle them.  The real problem is that this flag probably
	 * should be 0 on AVR32 as it is not supported on this
	 * platform--see CONFIG_HUGETLB_PAGE. */
	gfp &= ~(__GFP_COMP);

	size = PAGE_ALIGN(size);
	order = get_order(size);

	page = alloc_pages(gfp, order);
	if (!page)
		return NULL;
	split_page(page, order);

	/*
	 * When accessing physical memory with valid cache data, we
	 * get a cache hit even if the virtual memory region is marked
	 * as uncached.
	 *
	 * Since the memory is newly allocated, there is no point in
	 * doing a writeback. If the previous owner cares, he should
	 * have flushed the cache before releasing the memory.
	 */
	invalidate_dcache_region(phys_to_virt(page_to_phys(page)), size);

	*handle = page_to_bus(page);
	free = page + (size >> PAGE_SHIFT);
	end = page + (1 << order);

	/*
	 * Free any unused pages
	 */
	while (free < end) {
		__free_page(free);
		free++;
	}

	return page;
}