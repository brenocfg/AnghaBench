#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  val; } ;
typedef  TYPE_1__ swp_entry_t ;
struct page {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PageLocked (struct page*) ; 
 int /*<<< orphan*/  PageTransHuge (struct page*) ; 
 int /*<<< orphan*/  PageUptodate (struct page*) ; 
 int /*<<< orphan*/  SetPageDirty (struct page*) ; 
 int /*<<< orphan*/  VM_BUG_ON (int) ; 
 int __GFP_HIGH ; 
 int __GFP_NOMEMALLOC ; 
 int __GFP_NOWARN ; 
 int add_to_swap_cache (struct page*,TYPE_1__,int) ; 
 TYPE_1__ get_swap_page () ; 
 int /*<<< orphan*/  split_huge_page (struct page*) ; 
 int /*<<< orphan*/  swapcache_free (TYPE_1__,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

int add_to_swap(struct page *page)
{
	swp_entry_t entry;
	int err;

	VM_BUG_ON(!PageLocked(page));
	VM_BUG_ON(!PageUptodate(page));

	entry = get_swap_page();
	if (!entry.val)
		return 0;

	if (unlikely(PageTransHuge(page)))
		if (unlikely(split_huge_page(page))) {
			swapcache_free(entry, NULL);
			return 0;
		}

	/*
	 * Radix-tree node allocations from PF_MEMALLOC contexts could
	 * completely exhaust the page allocator. __GFP_NOMEMALLOC
	 * stops emergency reserves from being allocated.
	 *
	 * TODO: this could cause a theoretical memory reclaim
	 * deadlock in the swap out path.
	 */
	/*
	 * Add it to the swap cache and mark it dirty
	 */
	err = add_to_swap_cache(page, entry,
			__GFP_HIGH|__GFP_NOMEMALLOC|__GFP_NOWARN);

	if (!err) {	/* Success */
		SetPageDirty(page);
		return 1;
	} else {	/* -ENOMEM radix-tree allocation failure */
		/*
		 * add_to_swap_cache() doesn't return -EEXIST, so we can safely
		 * clear SWAP_HAS_CACHE flag.
		 */
		swapcache_free(entry, NULL);
		return 0;
	}
}