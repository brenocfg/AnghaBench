#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  val; } ;
typedef  TYPE_1__ swp_entry_t ;
struct page {int dummy; } ;
struct address_space {int dummy; } ;
typedef  int /*<<< orphan*/  pgoff_t ;

/* Variables and functions */
 unsigned char PageUptodate (struct page*) ; 
 struct page* find_get_page (struct address_space*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  page_cache_release (struct page*) ; 
 TYPE_1__ radix_to_swp_entry (struct page*) ; 
 scalar_t__ radix_tree_exceptional_entry (struct page*) ; 
 struct address_space swapper_space ; 

__attribute__((used)) static unsigned char mincore_page(struct address_space *mapping, pgoff_t pgoff)
{
	unsigned char present = 0;
	struct page *page;

	/*
	 * When tmpfs swaps out a page from a file, any process mapping that
	 * file will not get a swp_entry_t in its pte, but rather it is like
	 * any other file mapping (ie. marked !present and faulted in with
	 * tmpfs's .fault). So swapped out tmpfs mappings are tested here.
	 */
	page = find_get_page(mapping, pgoff);
#ifdef CONFIG_SWAP
	/* shmem/tmpfs may return swap: account for swapcache page too. */
	if (radix_tree_exceptional_entry(page)) {
		swp_entry_t swap = radix_to_swp_entry(page);
		page = find_get_page(&swapper_space, swap.val);
	}
#endif
	if (page) {
		present = PageUptodate(page);
		page_cache_release(page);
	}

	return present;
}