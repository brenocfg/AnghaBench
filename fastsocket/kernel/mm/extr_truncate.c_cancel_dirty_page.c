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
struct page {struct address_space* mapping; } ;
struct address_space {int /*<<< orphan*/  backing_dev_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  BDI_RECLAIMABLE ; 
 int /*<<< orphan*/  NR_FILE_DIRTY ; 
 scalar_t__ TestClearPageDirty (struct page*) ; 
 int /*<<< orphan*/  dec_bdi_stat (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dec_zone_page_state (struct page*,int /*<<< orphan*/ ) ; 
 scalar_t__ mapping_cap_account_dirty (struct address_space*) ; 
 int /*<<< orphan*/  task_io_account_cancelled_write (unsigned int) ; 

void cancel_dirty_page(struct page *page, unsigned int account_size)
{
	if (TestClearPageDirty(page)) {
		struct address_space *mapping = page->mapping;
		if (mapping && mapping_cap_account_dirty(mapping)) {
			dec_zone_page_state(page, NR_FILE_DIRTY);
			dec_bdi_stat(mapping->backing_dev_info,
					BDI_RECLAIMABLE);
			if (account_size)
				task_io_account_cancelled_write(account_size);
		}
	}
}