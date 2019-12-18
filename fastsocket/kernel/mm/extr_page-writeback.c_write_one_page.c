#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct writeback_control {int nr_to_write; int /*<<< orphan*/  sync_mode; } ;
struct page {struct address_space* mapping; } ;
struct address_space {TYPE_1__* a_ops; } ;
struct TYPE_2__ {int (* writepage ) (struct page*,struct writeback_control*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EIO ; 
 scalar_t__ PageError (struct page*) ; 
 int /*<<< orphan*/  PageLocked (struct page*) ; 
 int /*<<< orphan*/  WB_SYNC_ALL ; 
 scalar_t__ clear_page_dirty_for_io (struct page*) ; 
 int /*<<< orphan*/  page_cache_get (struct page*) ; 
 int /*<<< orphan*/  page_cache_release (struct page*) ; 
 int stub1 (struct page*,struct writeback_control*) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 
 int /*<<< orphan*/  wait_on_page_writeback (struct page*) ; 

int write_one_page(struct page *page, int wait)
{
	struct address_space *mapping = page->mapping;
	int ret = 0;
	struct writeback_control wbc = {
		.sync_mode = WB_SYNC_ALL,
		.nr_to_write = 1,
	};

	BUG_ON(!PageLocked(page));

	if (wait)
		wait_on_page_writeback(page);

	if (clear_page_dirty_for_io(page)) {
		page_cache_get(page);
		ret = mapping->a_ops->writepage(page, &wbc);
		if (ret == 0 && wait) {
			wait_on_page_writeback(page);
			if (PageError(page))
				ret = -EIO;
		}
		page_cache_release(page);
	} else {
		unlock_page(page);
	}
	return ret;
}