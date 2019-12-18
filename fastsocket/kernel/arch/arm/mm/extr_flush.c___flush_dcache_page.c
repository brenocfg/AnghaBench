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
struct page {int index; } ;
struct address_space {int dummy; } ;

/* Variables and functions */
 int PAGE_CACHE_SHIFT ; 
 int /*<<< orphan*/  __cpuc_flush_dcache_page (scalar_t__) ; 
 scalar_t__ cache_is_vipt_aliasing () ; 
 int /*<<< orphan*/  flush_pfn_alias (int /*<<< orphan*/ ,int) ; 
 scalar_t__ page_address (struct page*) ; 
 int /*<<< orphan*/  page_to_pfn (struct page*) ; 

void __flush_dcache_page(struct address_space *mapping, struct page *page)
{
	/*
	 * Writeback any data associated with the kernel mapping of this
	 * page.  This ensures that data in the physical page is mutually
	 * coherent with the kernels mapping.
	 */
#ifdef CONFIG_HIGHMEM
	/*
	 * kmap_atomic() doesn't set the page virtual address, and
	 * kunmap_atomic() takes care of cache flushing already.
	 */
	if (page_address(page))
#endif
		__cpuc_flush_dcache_page(page_address(page));

	/*
	 * If this is a page cache page, and we have an aliasing VIPT cache,
	 * we only need to do one flush - which would be at the relevant
	 * userspace colour, which is congruent with page->index.
	 */
	if (mapping && cache_is_vipt_aliasing())
		flush_pfn_alias(page_to_pfn(page),
				page->index << PAGE_CACHE_SHIFT);
}