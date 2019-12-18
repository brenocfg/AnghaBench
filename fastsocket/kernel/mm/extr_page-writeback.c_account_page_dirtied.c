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
 int /*<<< orphan*/  NR_FILE_DIRTY ; 
 int /*<<< orphan*/  PAGE_CACHE_SIZE ; 
 int /*<<< orphan*/  __inc_bdi_stat (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __inc_zone_page_state (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current ; 
 scalar_t__ mapping_cap_account_dirty (struct address_space*) ; 
 int /*<<< orphan*/  task_dirty_inc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  task_io_account_write (int /*<<< orphan*/ ) ; 

void account_page_dirtied(struct page *page, struct address_space *mapping)
{
	if (mapping_cap_account_dirty(mapping)) {
		__inc_zone_page_state(page, NR_FILE_DIRTY);
		__inc_bdi_stat(mapping->backing_dev_info, BDI_RECLAIMABLE);
		task_dirty_inc(current);
		task_io_account_write(PAGE_CACHE_SIZE);
	}
}