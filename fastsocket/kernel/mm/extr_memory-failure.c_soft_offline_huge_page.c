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
struct page {int /*<<< orphan*/  flags; int /*<<< orphan*/  lru; } ;

/* Variables and functions */
 int EBUSY ; 
 int EIO ; 
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MIGRATE_SYNC ; 
 int /*<<< orphan*/  MPOL_MF_MOVE_ALL ; 
 scalar_t__ PageHWPoison (struct page*) ; 
 int /*<<< orphan*/  atomic_long_add (int,int /*<<< orphan*/ *) ; 
 struct page* compound_head (struct page*) ; 
 int compound_trans_order (struct page*) ; 
 int /*<<< orphan*/  dequeue_hwpoisoned_huge_page (struct page*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_page (struct page*) ; 
 int migrate_huge_pages (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  new_page ; 
 int /*<<< orphan*/  num_poisoned_pages ; 
 unsigned long page_to_pfn (struct page*) ; 
 int /*<<< orphan*/  pagelist ; 
 int /*<<< orphan*/  pr_info (char*,unsigned long,...) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  set_page_hwpoison_huge_page (struct page*) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

__attribute__((used)) static int soft_offline_huge_page(struct page *page, int flags)
{
	int ret;
	unsigned long pfn = page_to_pfn(page);
	struct page *hpage = compound_head(page);
	LIST_HEAD(pagelist);

	/*
	 * This double-check of PageHWPoison is to avoid the race with
	 * memory_failure(). See also comment in __soft_offline_page().
	 */
	lock_page(hpage);
	if (PageHWPoison(hpage)) {
		unlock_page(hpage);
		put_page(hpage);
		pr_info("soft offline: %#lx hugepage already poisoned\n", pfn);
		return -EBUSY;
	}
	unlock_page(hpage);

	/* Keep page count to indicate a given hugepage is isolated. */

	list_add(&hpage->lru, &pagelist);
	ret = migrate_huge_pages(&pagelist, new_page, MPOL_MF_MOVE_ALL, false,
				MIGRATE_SYNC);
	if (ret) {
		pr_info("soft offline: %#lx: migration failed %d, type %lx\n",
			pfn, ret, page->flags);
		if (ret > 0)
			ret = -EIO;
	} else {
		set_page_hwpoison_huge_page(hpage);
		dequeue_hwpoisoned_huge_page(hpage);
		atomic_long_add(1 << compound_trans_order(hpage),
				&num_poisoned_pages);
	}
	return ret;
}