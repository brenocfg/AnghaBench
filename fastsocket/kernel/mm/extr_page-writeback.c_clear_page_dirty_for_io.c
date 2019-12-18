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
struct address_space {int /*<<< orphan*/  backing_dev_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  BDI_RECLAIMABLE ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  NR_FILE_DIRTY ; 
 int /*<<< orphan*/  PageLocked (struct page*) ; 
 int TestClearPageDirty (struct page*) ; 
 int /*<<< orphan*/  dec_bdi_stat (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dec_zone_page_state (struct page*,int /*<<< orphan*/ ) ; 
 scalar_t__ mapping_cap_account_dirty (struct address_space*) ; 
 struct address_space* page_mapping (struct page*) ; 
 scalar_t__ page_mkclean (struct page*) ; 
 int /*<<< orphan*/  set_page_dirty (struct page*) ; 

int clear_page_dirty_for_io(struct page *page)
{
	struct address_space *mapping = page_mapping(page);

	BUG_ON(!PageLocked(page));

	if (mapping && mapping_cap_account_dirty(mapping)) {
		/*
		 * Yes, Virginia, this is indeed insane.
		 *
		 * We use this sequence to make sure that
		 *  (a) we account for dirty stats properly
		 *  (b) we tell the low-level filesystem to
		 *      mark the whole page dirty if it was
		 *      dirty in a pagetable. Only to then
		 *  (c) clean the page again and return 1 to
		 *      cause the writeback.
		 *
		 * This way we avoid all nasty races with the
		 * dirty bit in multiple places and clearing
		 * them concurrently from different threads.
		 *
		 * Note! Normally the "set_page_dirty(page)"
		 * has no effect on the actual dirty bit - since
		 * that will already usually be set. But we
		 * need the side effects, and it can help us
		 * avoid races.
		 *
		 * We basically use the page "master dirty bit"
		 * as a serialization point for all the different
		 * threads doing their things.
		 */
		if (page_mkclean(page))
			set_page_dirty(page);
		/*
		 * We carefully synchronise fault handlers against
		 * installing a dirty pte and marking the page dirty
		 * at this point. We do this by having them hold the
		 * page lock at some point after installing their
		 * pte, but before marking the page dirty.
		 * Pages are always locked coming in here, so we get
		 * the desired exclusion. See mm/memory.c:do_wp_page()
		 * for more comments.
		 */
		if (TestClearPageDirty(page)) {
			dec_zone_page_state(page, NR_FILE_DIRTY);
			dec_bdi_stat(mapping->backing_dev_info,
					BDI_RECLAIMABLE);
			return 1;
		}
		return 0;
	}
	return TestClearPageDirty(page);
}