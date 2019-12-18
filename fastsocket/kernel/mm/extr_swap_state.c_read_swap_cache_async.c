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
struct vm_area_struct {int dummy; } ;
struct page {int dummy; } ;
typedef  int gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  ClearPageSwapBacked (struct page*) ; 
 int EEXIST ; 
 int ENOMEM ; 
 int GFP_KERNEL ; 
 int /*<<< orphan*/  SetPageSwapBacked (struct page*) ; 
 int __add_to_swap_cache (struct page*,TYPE_1__) ; 
 int /*<<< orphan*/  __clear_page_locked (struct page*) ; 
 int /*<<< orphan*/  __set_page_locked (struct page*) ; 
 struct page* alloc_page_vma (int,struct vm_area_struct*,unsigned long) ; 
 int /*<<< orphan*/  cond_resched () ; 
 struct page* find_get_page (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  lru_cache_add_anon (struct page*) ; 
 int /*<<< orphan*/  page_cache_release (struct page*) ; 
 int radix_tree_preload (int) ; 
 int /*<<< orphan*/  radix_tree_preload_end () ; 
 int /*<<< orphan*/  swap_readpage (struct page*) ; 
 int /*<<< orphan*/  swapcache_free (TYPE_1__,int /*<<< orphan*/ *) ; 
 int swapcache_prepare (TYPE_1__) ; 
 int /*<<< orphan*/  swapper_space ; 

struct page *read_swap_cache_async(swp_entry_t entry, gfp_t gfp_mask,
			struct vm_area_struct *vma, unsigned long addr)
{
	struct page *found_page, *new_page = NULL;
	int err;

	do {
		/*
		 * First check the swap cache.  Since this is normally
		 * called after lookup_swap_cache() failed, re-calling
		 * that would confuse statistics.
		 */
		found_page = find_get_page(&swapper_space, entry.val);
		if (found_page)
			break;

		/*
		 * Get a new page to read into from swap.
		 */
		if (!new_page) {
			new_page = alloc_page_vma(gfp_mask, vma, addr);
			if (!new_page)
				break;		/* Out of memory */
		}

		/*
		 * call radix_tree_preload() while we can wait.
		 */
		err = radix_tree_preload(gfp_mask & GFP_KERNEL);
		if (err)
			break;

		/*
		 * Swap entry may have been freed since our caller observed it.
		 */
		err = swapcache_prepare(entry);
		if (err == -EEXIST) {
			radix_tree_preload_end();
			/*
			 * We might race against get_swap_page() and stumble
			 * across a SWAP_HAS_CACHE swap_map entry whose page
			 * has not been brought into the swapcache yet, while
			 * the other end is scheduled away waiting on discard
			 * I/O completion at scan_swap_map().
			 *
			 * In order to avoid turning this transitory state
			 * into a permanent loop around this -EEXIST case
			 * if !CONFIG_PREEMPT and the I/O completion happens
			 * to be waiting on the CPU waitqueue where we are now
			 * busy looping, we just conditionally invoke the
			 * scheduler here, if there are some more important
			 * tasks to run.
			 */
			cond_resched();
			continue;
		}
		if (err) {		/* swp entry is obsolete ? */
			radix_tree_preload_end();
			break;
		}

		/* May fail (-ENOMEM) if radix-tree node allocation failed. */
		__set_page_locked(new_page);
		SetPageSwapBacked(new_page);
		err = __add_to_swap_cache(new_page, entry);
		if (likely(!err)) {
			radix_tree_preload_end();
			/*
			 * Initiate read into locked page and return.
			 */
			lru_cache_add_anon(new_page);
			swap_readpage(new_page);
			return new_page;
		}
		radix_tree_preload_end();
		ClearPageSwapBacked(new_page);
		__clear_page_locked(new_page);
		/*
		 * add_to_swap_cache() doesn't return -EEXIST, so we can safely
		 * clear SWAP_HAS_CACHE flag.
		 */
		swapcache_free(entry, NULL);
	} while (err != -ENOMEM);

	if (new_page)
		page_cache_release(new_page);
	return found_page;
}