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
struct page {struct address_space* mapping; int /*<<< orphan*/  index; } ;
struct address_space {int /*<<< orphan*/  backing_dev_info; int /*<<< orphan*/  nrpages; int /*<<< orphan*/  page_tree; } ;

/* Variables and functions */
 int /*<<< orphan*/  BDI_RECLAIMABLE ; 
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NR_FILE_DIRTY ; 
 int /*<<< orphan*/  NR_FILE_PAGES ; 
 int /*<<< orphan*/  NR_SHMEM ; 
 scalar_t__ PageDirty (struct page*) ; 
 scalar_t__ PageSwapBacked (struct page*) ; 
 int /*<<< orphan*/  __dec_zone_page_state (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dec_bdi_stat (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dec_zone_page_state (struct page*,int /*<<< orphan*/ ) ; 
 scalar_t__ mapping_cap_account_dirty (struct address_space*) ; 
 int /*<<< orphan*/  page_mapped (struct page*) ; 
 int /*<<< orphan*/  radix_tree_delete (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void __remove_from_page_cache(struct page *page)
{
	struct address_space *mapping = page->mapping;

	radix_tree_delete(&mapping->page_tree, page->index);
	page->mapping = NULL;
	/* Leave page->index set: truncation lookup relies upon it */
	mapping->nrpages--;
	__dec_zone_page_state(page, NR_FILE_PAGES);
	if (PageSwapBacked(page))
		__dec_zone_page_state(page, NR_SHMEM);
	BUG_ON(page_mapped(page));

	/*
	 * Some filesystems seem to re-dirty the page even after
	 * the VM has canceled the dirty bit (eg ext3 journaling).
	 *
	 * Fix it up by doing a final dirty accounting check after
	 * having removed the page entirely.
	 */
	if (PageDirty(page) && mapping_cap_account_dirty(mapping)) {
		dec_zone_page_state(page, NR_FILE_DIRTY);
		dec_bdi_stat(mapping->backing_dev_info, BDI_RECLAIMABLE);
	}
}