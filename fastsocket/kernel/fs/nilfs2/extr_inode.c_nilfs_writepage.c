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
struct writeback_control {scalar_t__ sync_mode; scalar_t__ for_reclaim; } ;
struct page {TYPE_1__* mapping; } ;
struct inode {int /*<<< orphan*/  i_ino; int /*<<< orphan*/  i_sb; } ;
struct TYPE_2__ {struct inode* host; } ;

/* Variables and functions */
 scalar_t__ WB_SYNC_ALL ; 
 int nilfs_construct_segment (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nilfs_flush_segment (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  redirty_page_for_writepage (struct writeback_control*,struct page*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

__attribute__((used)) static int nilfs_writepage(struct page *page, struct writeback_control *wbc)
{
	struct inode *inode = page->mapping->host;
	int err;

	redirty_page_for_writepage(wbc, page);
	unlock_page(page);

	if (wbc->sync_mode == WB_SYNC_ALL) {
		err = nilfs_construct_segment(inode->i_sb);
		if (unlikely(err))
			return err;
	} else if (wbc->for_reclaim)
		nilfs_flush_segment(inode->i_sb, inode->i_ino);

	return 0;
}