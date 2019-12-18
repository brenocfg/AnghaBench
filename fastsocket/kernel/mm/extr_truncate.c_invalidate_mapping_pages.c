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
struct pagevec {struct page** pages; } ;
struct page {scalar_t__ index; } ;
struct address_space {int dummy; } ;
typedef  scalar_t__ pgoff_t ;

/* Variables and functions */
 scalar_t__ PAGEVEC_SIZE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  cond_resched () ; 
 int /*<<< orphan*/  deactivate_page (struct page*) ; 
 unsigned long invalidate_inode_page (struct page*) ; 
 int /*<<< orphan*/  mem_cgroup_uncharge_end () ; 
 int /*<<< orphan*/  mem_cgroup_uncharge_start () ; 
 scalar_t__ min (scalar_t__,scalar_t__) ; 
 int pagevec_count (struct pagevec*) ; 
 int /*<<< orphan*/  pagevec_init (struct pagevec*,int /*<<< orphan*/ ) ; 
 scalar_t__ pagevec_lookup (struct pagevec*,struct address_space*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  pagevec_release (struct pagevec*) ; 
 int /*<<< orphan*/  trylock_page (struct page*) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

unsigned long invalidate_mapping_pages(struct address_space *mapping,
		pgoff_t start, pgoff_t end)
{
	struct pagevec pvec;
	pgoff_t index = start;
	unsigned long ret;
	unsigned long count = 0;
	int i;

	/*
	 * Note: this function may get called on a shmem/tmpfs mapping:
	 * pagevec_lookup() might then return 0 prematurely (because it
	 * got a gangful of swap entries); but it's hardly worth worrying
	 * about - it can rarely have anything to free from such a mapping
	 * (most pages are dirty), and already skips over any difficulties.
	 */

	pagevec_init(&pvec, 0);
	while (index <= end && pagevec_lookup(&pvec, mapping, index,
			min(end - index, (pgoff_t)PAGEVEC_SIZE - 1) + 1)) {
		mem_cgroup_uncharge_start();
		for (i = 0; i < pagevec_count(&pvec); i++) {
			struct page *page = pvec.pages[i];

			/* We rely upon deletion not changing page->index */
			index = page->index;
			if (index > end)
				break;

			if (!trylock_page(page))
				continue;
			WARN_ON(page->index != index);
			ret = invalidate_inode_page(page);
			unlock_page(page);
			/*
			 * Invalidation is a hint that the page is no longer
			 * of interest and try to speed up its reclaim.
			 */
			if (!ret)
				deactivate_page(page);
			count += ret;
		}
		pagevec_release(&pvec);
		mem_cgroup_uncharge_end();
		cond_resched();
		index++;
	}
	return count;
}