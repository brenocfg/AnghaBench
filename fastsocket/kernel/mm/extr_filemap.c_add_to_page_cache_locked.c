#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct page {struct address_space* mapping; int /*<<< orphan*/  index; } ;
struct address_space {int /*<<< orphan*/  tree_lock; int /*<<< orphan*/  nrpages; int /*<<< orphan*/  page_tree; } ;
typedef  int /*<<< orphan*/  pgoff_t ;
typedef  int gfp_t ;
struct TYPE_2__ {int /*<<< orphan*/  mm; } ;

/* Variables and functions */
 int GFP_RECLAIM_MASK ; 
 int /*<<< orphan*/  NR_FILE_PAGES ; 
 int /*<<< orphan*/  PageLocked (struct page*) ; 
 int PageSwapBacked (struct page*) ; 
 int /*<<< orphan*/  VM_BUG_ON (int) ; 
 int __GFP_HIGHMEM ; 
 int /*<<< orphan*/  __inc_zone_page_state (struct page*,int /*<<< orphan*/ ) ; 
 TYPE_1__* current ; 
 scalar_t__ likely (int) ; 
 int mem_cgroup_cache_charge (struct page*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mem_cgroup_uncharge_cache_page (struct page*) ; 
 int /*<<< orphan*/  page_cache_get (struct page*) ; 
 int /*<<< orphan*/  page_cache_release (struct page*) ; 
 int radix_tree_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct page*) ; 
 int radix_tree_preload (int) ; 
 int /*<<< orphan*/  radix_tree_preload_end () ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

int add_to_page_cache_locked(struct page *page, struct address_space *mapping,
		pgoff_t offset, gfp_t gfp_mask)
{
	int error;

	VM_BUG_ON(!PageLocked(page));
	VM_BUG_ON(PageSwapBacked(page));

	error = mem_cgroup_cache_charge(page, current->mm,
					gfp_mask & GFP_RECLAIM_MASK);
	if (error)
		goto out;

	error = radix_tree_preload(gfp_mask & ~__GFP_HIGHMEM);
	if (error == 0) {
		page_cache_get(page);
		page->mapping = mapping;
		page->index = offset;

		spin_lock_irq(&mapping->tree_lock);
		error = radix_tree_insert(&mapping->page_tree, offset, page);
		if (likely(!error)) {
			mapping->nrpages++;
			__inc_zone_page_state(page, NR_FILE_PAGES);
			spin_unlock_irq(&mapping->tree_lock);
		} else {
			page->mapping = NULL;
			/* Leave page->index set: truncation relies upon it */
			spin_unlock_irq(&mapping->tree_lock);
			mem_cgroup_uncharge_cache_page(page);
			page_cache_release(page);
		}
		radix_tree_preload_end();
	} else
		mem_cgroup_uncharge_cache_page(page);
out:
	return error;
}