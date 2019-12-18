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
struct swap_info_struct {int /*<<< orphan*/  type; } ;
struct page {int dummy; } ;

/* Variables and functions */
 struct page* find_get_page (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  page_cache_release (struct page*) ; 
 int /*<<< orphan*/  swapper_space ; 
 TYPE_1__ swp_entry (int /*<<< orphan*/ ,unsigned long) ; 
 int try_to_free_swap (struct page*) ; 
 scalar_t__ trylock_page (struct page*) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

__attribute__((used)) static int
__try_to_reclaim_swap(struct swap_info_struct *si, unsigned long offset)
{
	swp_entry_t entry = swp_entry(si->type, offset);
	struct page *page;
	int ret = 0;

	page = find_get_page(&swapper_space, entry.val);
	if (!page)
		return 0;
	/*
	 * This function is called from scan_swap_map() and it's called
	 * by vmscan.c at reclaiming pages. So, we hold a lock on a page, here.
	 * We have to use trylock for avoiding deadlock. This is a special
	 * case and you should use try_to_free_swap() with explicit lock_page()
	 * in usual operations.
	 */
	if (trylock_page(page)) {
		ret = try_to_free_swap(page);
		unlock_page(page);
	}
	page_cache_release(page);
	return ret;
}