#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  val; } ;
typedef  TYPE_1__ swp_entry_t ;
struct swap_info_struct {int dummy; } ;
struct page {int dummy; } ;

/* Variables and functions */
 scalar_t__ PageSwapCache (struct page*) ; 
 int /*<<< orphan*/  PageWriteback (struct page*) ; 
 scalar_t__ SWAP_HAS_CACHE ; 
 int /*<<< orphan*/  SetPageDirty (struct page*) ; 
 int /*<<< orphan*/  delete_from_swap_cache (struct page*) ; 
 struct page* find_get_page (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ non_swap_entry (TYPE_1__) ; 
 int /*<<< orphan*/  page_cache_release (struct page*) ; 
 int /*<<< orphan*/  page_mapped (struct page*) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ swap_entry_free (struct swap_info_struct*,TYPE_1__,int) ; 
 struct swap_info_struct* swap_info_get (TYPE_1__) ; 
 int /*<<< orphan*/  swap_lock ; 
 int /*<<< orphan*/  swapper_space ; 
 int /*<<< orphan*/  trylock_page (struct page*) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 
 scalar_t__ vm_swap_full () ; 

int free_swap_and_cache(swp_entry_t entry)
{
	struct swap_info_struct *p;
	struct page *page = NULL;

	if (non_swap_entry(entry))
		return 1;

	p = swap_info_get(entry);
	if (p) {
		if (swap_entry_free(p, entry, 1) == SWAP_HAS_CACHE) {
			page = find_get_page(&swapper_space, entry.val);
			if (page && !trylock_page(page)) {
				page_cache_release(page);
				page = NULL;
			}
		}
		spin_unlock(&swap_lock);
	}
	if (page) {
		/*
		 * Not mapped elsewhere, or swap space full? Free it!
		 * Also recheck PageSwapCache now page is locked (above).
		 */
		if (PageSwapCache(page) && !PageWriteback(page) &&
				(!page_mapped(page) || vm_swap_full())) {
			delete_from_swap_cache(page);
			SetPageDirty(page);
		}
		unlock_page(page);
		page_cache_release(page);
	}
	return p != NULL;
}