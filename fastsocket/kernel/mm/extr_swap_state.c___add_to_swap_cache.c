#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned long val; } ;
typedef  TYPE_1__ swp_entry_t ;
struct page {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  tree_lock; int /*<<< orphan*/  page_tree; } ;

/* Variables and functions */
 int /*<<< orphan*/  ClearPageSwapCache (struct page*) ; 
 int EEXIST ; 
 int /*<<< orphan*/  INC_CACHE_INFO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NR_FILE_PAGES ; 
 int /*<<< orphan*/  PageLocked (struct page*) ; 
 int /*<<< orphan*/  PageSwapBacked (struct page*) ; 
 int PageSwapCache (struct page*) ; 
 int /*<<< orphan*/  SetPageSwapCache (struct page*) ; 
 int /*<<< orphan*/  VM_BUG_ON (int) ; 
 int /*<<< orphan*/  __inc_zone_page_state (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_total ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  page_cache_get (struct page*) ; 
 int /*<<< orphan*/  page_cache_release (struct page*) ; 
 int radix_tree_insert (int /*<<< orphan*/ *,unsigned long,struct page*) ; 
 int /*<<< orphan*/  set_page_private (struct page*,unsigned long) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 TYPE_2__ swapper_space ; 
 int /*<<< orphan*/  total_swapcache_pages ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int __add_to_swap_cache(struct page *page, swp_entry_t entry)
{
	int error;

	VM_BUG_ON(!PageLocked(page));
	VM_BUG_ON(PageSwapCache(page));
	VM_BUG_ON(!PageSwapBacked(page));

	page_cache_get(page);
	SetPageSwapCache(page);
	set_page_private(page, entry.val);

	spin_lock_irq(&swapper_space.tree_lock);
	error = radix_tree_insert(&swapper_space.page_tree, entry.val, page);
	if (likely(!error)) {
		total_swapcache_pages++;
		__inc_zone_page_state(page, NR_FILE_PAGES);
		INC_CACHE_INFO(add_total);
	}
	spin_unlock_irq(&swapper_space.tree_lock);

	if (unlikely(error)) {
		/*
		 * Only the context which have set SWAP_HAS_CACHE flag
		 * would call add_to_swap_cache().
		 * So add_to_swap_cache() doesn't returns -EEXIST.
		 */
		VM_BUG_ON(error == -EEXIST);
		set_page_private(page, 0UL);
		ClearPageSwapCache(page);
		page_cache_release(page);
	}

	return error;
}