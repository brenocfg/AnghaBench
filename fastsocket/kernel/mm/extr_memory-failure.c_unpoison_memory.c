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
struct page {int dummy; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  PageHWPoison (struct page*) ; 
 scalar_t__ PageHuge (struct page*) ; 
 scalar_t__ TestClearPageHWPoison (struct page*) ; 
 int /*<<< orphan*/  atomic_long_sub (unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_page_hwpoison_huge_page (struct page*) ; 
 struct page* compound_head (struct page*) ; 
 int compound_trans_order (struct page*) ; 
 int /*<<< orphan*/  get_page_unless_zero (struct page*) ; 
 int /*<<< orphan*/  lock_page_nosync (struct page*) ; 
 int /*<<< orphan*/  num_poisoned_pages ; 
 struct page* pfn_to_page (unsigned long) ; 
 int /*<<< orphan*/  pfn_valid (unsigned long) ; 
 int /*<<< orphan*/  pr_info (char*,unsigned long) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

int unpoison_memory(unsigned long pfn)
{
	struct page *page;
	struct page *p;
	int freeit = 0;
	unsigned int nr_pages;

	if (!pfn_valid(pfn))
		return -ENXIO;

	p = pfn_to_page(pfn);
	page = compound_head(p);

	if (!PageHWPoison(p)) {
		pr_info("MCE: Page was already unpoisoned %#lx\n", pfn);
		return 0;
	}

	nr_pages = 1 << compound_trans_order(page);

	if (!get_page_unless_zero(page)) {
		/*
		 * Since HWPoisoned hugepage should have non-zero refcount,
		 * race between memory failure and unpoison seems to happen.
		 * In such case unpoison fails and memory failure runs
		 * to the end.
		 */
		if (PageHuge(page)) {
			pr_info("MCE: Memory failure is now running on free hugepage %#lx\n", pfn);
			return 0;
		}
		if (TestClearPageHWPoison(p))
			atomic_long_sub(nr_pages, &num_poisoned_pages);
		pr_info("MCE: Software-unpoisoned free page %#lx\n", pfn);
		return 0;
	}

	lock_page_nosync(page);
	/*
	 * This test is racy because PG_hwpoison is set outside of page lock.
	 * That's acceptable because that won't trigger kernel panic. Instead,
	 * the PG_hwpoison page will be caught and isolated on the entrance to
	 * the free buddy page pool.
	 */
	if (TestClearPageHWPoison(page)) {
		pr_info("MCE: Software-unpoisoned page %#lx\n", pfn);
		atomic_long_sub(nr_pages, &num_poisoned_pages);
		freeit = 1;
		if (PageHuge(page))
			clear_page_hwpoison_huge_page(page);
	}
	unlock_page(page);

	put_page(page);
	if (freeit)
		put_page(page);

	return 0;
}