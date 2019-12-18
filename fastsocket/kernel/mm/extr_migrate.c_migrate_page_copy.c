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
struct page {int /*<<< orphan*/ * mapping; } ;

/* Variables and functions */
 int /*<<< orphan*/  ClearPagePrivate (struct page*) ; 
 int /*<<< orphan*/  ClearPageSwapCache (struct page*) ; 
 scalar_t__ PageChecked (struct page*) ; 
 scalar_t__ PageDirty (struct page*) ; 
 scalar_t__ PageError (struct page*) ; 
 scalar_t__ PageHuge (struct page*) ; 
 scalar_t__ PageMappedToDisk (struct page*) ; 
 scalar_t__ PageReferenced (struct page*) ; 
 int /*<<< orphan*/  PageUnevictable (struct page*) ; 
 scalar_t__ PageUptodate (struct page*) ; 
 scalar_t__ PageWriteback (struct page*) ; 
 int /*<<< orphan*/  SetPageActive (struct page*) ; 
 int /*<<< orphan*/  SetPageChecked (struct page*) ; 
 int /*<<< orphan*/  SetPageError (struct page*) ; 
 int /*<<< orphan*/  SetPageMappedToDisk (struct page*) ; 
 int /*<<< orphan*/  SetPageReferenced (struct page*) ; 
 int /*<<< orphan*/  SetPageUptodate (struct page*) ; 
 scalar_t__ TestClearPageActive (struct page*) ; 
 int /*<<< orphan*/  VM_BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __set_page_dirty_nobuffers (struct page*) ; 
 int /*<<< orphan*/  clear_page_dirty_for_io (struct page*) ; 
 int /*<<< orphan*/  copy_highpage (struct page*,struct page*) ; 
 int /*<<< orphan*/  copy_huge_page (struct page*,struct page*) ; 
 int /*<<< orphan*/  end_page_writeback (struct page*) ; 
 int /*<<< orphan*/  ksm_migrate_page (struct page*,struct page*) ; 
 int /*<<< orphan*/  mlock_migrate_page (struct page*,struct page*) ; 
 int /*<<< orphan*/  set_page_private (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unevictable_migrate_page (struct page*,struct page*) ; 

void migrate_page_copy(struct page *newpage, struct page *page)
{
	if (PageHuge(page))
		copy_huge_page(newpage, page);
	else
		copy_highpage(newpage, page);

	if (PageError(page))
		SetPageError(newpage);
	if (PageReferenced(page))
		SetPageReferenced(newpage);
	if (PageUptodate(page))
		SetPageUptodate(newpage);
	if (TestClearPageActive(page)) {
		VM_BUG_ON(PageUnevictable(page));
		SetPageActive(newpage);
	} else
		unevictable_migrate_page(newpage, page);
	if (PageChecked(page))
		SetPageChecked(newpage);
	if (PageMappedToDisk(page))
		SetPageMappedToDisk(newpage);

	if (PageDirty(page)) {
		clear_page_dirty_for_io(page);
		/*
		 * Want to mark the page and the radix tree as dirty, and
		 * redo the accounting that clear_page_dirty_for_io undid,
		 * but we can't use set_page_dirty because that function
		 * is actually a signal that all of the page has become dirty.
		 * Wheras only part of our page may be dirty.
		 */
		__set_page_dirty_nobuffers(newpage);
 	}

	mlock_migrate_page(newpage, page);
	ksm_migrate_page(newpage, page);
	/*
	 * Please do not reorder this without considering how mm/ksm.c's
	 * get_ksm_page() depends upon ksm_migrate_page() and PageSwapCache().
	 */
	ClearPageSwapCache(page);
	ClearPagePrivate(page);
	set_page_private(page, 0);
	page->mapping = NULL;

	/*
	 * If any waiters have accumulated on the new page then
	 * wake them up.
	 */
	if (PageWriteback(newpage))
		end_page_writeback(newpage);
}