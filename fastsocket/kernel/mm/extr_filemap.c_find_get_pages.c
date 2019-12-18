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
typedef  void page ;
struct address_space {int /*<<< orphan*/  page_tree; } ;
typedef  unsigned int pgoff_t ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (unsigned int) ; 
 int /*<<< orphan*/  page_cache_get_speculative (void*) ; 
 int /*<<< orphan*/  page_cache_release (void*) ; 
 scalar_t__ radix_tree_deref_retry (void*) ; 
 void* radix_tree_deref_slot (void**) ; 
 scalar_t__ radix_tree_exception (void*) ; 
 unsigned int radix_tree_gang_lookup_slot (int /*<<< orphan*/ *,void***,int /*<<< orphan*/ *,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 scalar_t__ unlikely (int) ; 

unsigned find_get_pages(struct address_space *mapping, pgoff_t start,
			    unsigned int nr_pages, struct page **pages)
{
	unsigned int i;
	unsigned int ret;
	unsigned int nr_found;

	rcu_read_lock();
restart:
	nr_found = radix_tree_gang_lookup_slot(&mapping->page_tree,
				(void ***)pages, NULL, start, nr_pages);
	ret = 0;
	for (i = 0; i < nr_found; i++) {
		struct page *page;
repeat:
		page = radix_tree_deref_slot((void **)pages[i]);
		if (unlikely(!page))
			continue;

		if (radix_tree_exception(page)) {
			if (radix_tree_deref_retry(page)) {
				/*
				 * Transient condition which can only trigger
				 * when entry at index 0 moves out of or back
				 * to root: none yet gotten, safe to restart.
				 */
				WARN_ON(start | i);
				goto restart;
			}
			/*
			 * Otherwise, shmem/tmpfs must be storing a swap entry
			 * here as an exceptional entry: so skip over it -
			 * we only reach this from invalidate_mapping_pages().
			 */
			continue;
		}

		if (!page_cache_get_speculative(page))
			goto repeat;

		/* Has the page moved? */
		if (unlikely(page != *((void **)pages[i]))) {
			page_cache_release(page);
			goto repeat;
		}

		pages[ret] = page;
		ret++;
	}
	rcu_read_unlock();
	return ret;
}