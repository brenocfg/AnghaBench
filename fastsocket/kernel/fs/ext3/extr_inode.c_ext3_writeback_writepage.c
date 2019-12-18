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
struct writeback_control {int dummy; } ;
struct page {TYPE_1__* mapping; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
typedef  int /*<<< orphan*/  handle_t ;
struct TYPE_2__ {struct inode* host; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NOBH ; 
 int /*<<< orphan*/  PAGE_CACHE_SIZE ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int block_write_full_page (struct page*,int /*<<< orphan*/ *,struct writeback_control*) ; 
 int /*<<< orphan*/  buffer_unmapped ; 
 int /*<<< orphan*/ * ext3_get_block ; 
 scalar_t__ ext3_journal_current_handle () ; 
 int /*<<< orphan*/ * ext3_journal_start (struct inode*,int /*<<< orphan*/ ) ; 
 int ext3_journal_stop (int /*<<< orphan*/ *) ; 
 scalar_t__ ext3_should_writeback_data (struct inode*) ; 
 int /*<<< orphan*/  ext3_writepage_trans_blocks (struct inode*) ; 
 int nobh_writepage (struct page*,int /*<<< orphan*/ *,struct writeback_control*) ; 
 int /*<<< orphan*/  page_buffers (struct page*) ; 
 scalar_t__ page_has_buffers (struct page*) ; 
 int /*<<< orphan*/  redirty_page_for_writepage (struct writeback_control*,struct page*) ; 
 scalar_t__ test_opt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_ext3_writeback_writepage (struct page*) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 
 int /*<<< orphan*/  walk_page_buffers (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ext3_writeback_writepage(struct page *page,
				struct writeback_control *wbc)
{
	struct inode *inode = page->mapping->host;
	handle_t *handle = NULL;
	int ret = 0;
	int err;

	if (ext3_journal_current_handle())
		goto out_fail;

	trace_ext3_writeback_writepage(page);
	if (page_has_buffers(page)) {
		if (!walk_page_buffers(NULL, page_buffers(page), 0,
				      PAGE_CACHE_SIZE, NULL, buffer_unmapped)) {
			/* Provide NULL get_block() to catch bugs if buffers
			 * weren't really mapped */
			return block_write_full_page(page, NULL, wbc);
		}
	}

	handle = ext3_journal_start(inode, ext3_writepage_trans_blocks(inode));
	if (IS_ERR(handle)) {
		ret = PTR_ERR(handle);
		goto out_fail;
	}

	if (test_opt(inode->i_sb, NOBH) && ext3_should_writeback_data(inode))
		ret = nobh_writepage(page, ext3_get_block, wbc);
	else
		ret = block_write_full_page(page, ext3_get_block, wbc);

	err = ext3_journal_stop(handle);
	if (!ret)
		ret = err;
	return ret;

out_fail:
	redirty_page_for_writepage(wbc, page);
	unlock_page(page);
	return ret;
}