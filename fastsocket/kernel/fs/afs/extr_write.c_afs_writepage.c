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
struct writeback_control {int nr_to_write; int encountered_congestion; scalar_t__ nonblocking; } ;
struct page {int /*<<< orphan*/  index; TYPE_1__* mapping; } ;
struct backing_dev_info {int dummy; } ;
struct afs_writeback {int dummy; } ;
struct TYPE_2__ {struct backing_dev_info* backing_dev_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _enter (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _leave (char*,...) ; 
 int afs_write_back_from_locked_page (struct afs_writeback*,struct page*) ; 
 scalar_t__ bdi_write_congested (struct backing_dev_info*) ; 
 scalar_t__ page_private (struct page*) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

int afs_writepage(struct page *page, struct writeback_control *wbc)
{
	struct backing_dev_info *bdi = page->mapping->backing_dev_info;
	struct afs_writeback *wb;
	int ret;

	_enter("{%lx},", page->index);

	wb = (struct afs_writeback *) page_private(page);
	ASSERT(wb != NULL);

	ret = afs_write_back_from_locked_page(wb, page);
	unlock_page(page);
	if (ret < 0) {
		_leave(" = %d", ret);
		return 0;
	}

	wbc->nr_to_write -= ret;
	if (wbc->nonblocking && bdi_write_congested(bdi))
		wbc->encountered_congestion = 1;

	_leave(" = 0");
	return 0;
}