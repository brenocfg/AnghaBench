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
typedef  int /*<<< orphan*/  swp_entry_t ;
struct vm_area_struct {int dummy; } ;
struct page {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  lru_add_drain () ; 
 int /*<<< orphan*/  page_cache_release (struct page*) ; 
 struct page* read_swap_cache_async (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vm_area_struct*,unsigned long) ; 
 int /*<<< orphan*/  swp_entry (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  swp_type (int /*<<< orphan*/ ) ; 
 int valid_swaphandles (int /*<<< orphan*/ ,unsigned long*) ; 

struct page *swapin_readahead(swp_entry_t entry, gfp_t gfp_mask,
			struct vm_area_struct *vma, unsigned long addr)
{
	int nr_pages;
	struct page *page;
	unsigned long offset;
	unsigned long end_offset;

	/*
	 * Get starting offset for readaround, and number of pages to read.
	 * Adjust starting address by readbehind (for NUMA interleave case)?
	 * No, it's very unlikely that swap layout would follow vma layout,
	 * more likely that neighbouring swap pages came from the same node:
	 * so use the same "addr" to choose the same node for each swap read.
	 */
	nr_pages = valid_swaphandles(entry, &offset);
	for (end_offset = offset + nr_pages; offset < end_offset; offset++) {
		/* Ok, do the async read-ahead now */
		page = read_swap_cache_async(swp_entry(swp_type(entry), offset),
						gfp_mask, vma, addr);
		if (!page)
			break;
		page_cache_release(page);
	}
	lru_add_drain();	/* Push any new pages onto the LRU now */
	return read_swap_cache_async(entry, gfp_mask, vma, addr);
}