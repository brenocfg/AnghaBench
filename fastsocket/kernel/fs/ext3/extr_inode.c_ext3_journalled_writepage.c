#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct writeback_control {int dummy; } ;
struct page {TYPE_1__* mapping; } ;
struct inode {int dummy; } ;
typedef  int /*<<< orphan*/  handle_t ;
struct TYPE_4__ {int /*<<< orphan*/  i_state; } ;
struct TYPE_3__ {struct inode* host; } ;

/* Variables and functions */
 int /*<<< orphan*/  ClearPageChecked (struct page*) ; 
 TYPE_2__* EXT3_I (struct inode*) ; 
 int /*<<< orphan*/  EXT3_STATE_JDATA ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PAGE_CACHE_SIZE ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 scalar_t__ PageChecked (struct page*) ; 
 int block_prepare_write (struct page*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int block_write_full_page (struct page*,int /*<<< orphan*/ ,struct writeback_control*) ; 
 int /*<<< orphan*/  do_journal_get_write_access ; 
 int /*<<< orphan*/  ext3_get_block ; 
 scalar_t__ ext3_journal_current_handle () ; 
 int /*<<< orphan*/ * ext3_journal_start (struct inode*,int /*<<< orphan*/ ) ; 
 int ext3_journal_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ext3_journalled_get_block ; 
 int /*<<< orphan*/  ext3_writepage_trans_blocks (struct inode*) ; 
 int /*<<< orphan*/  page_buffers (struct page*) ; 
 int /*<<< orphan*/  page_has_buffers (struct page*) ; 
 int /*<<< orphan*/  redirty_page_for_writepage (struct writeback_control*,struct page*) ; 
 int /*<<< orphan*/  trace_ext3_journalled_writepage (struct page*) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 
 int walk_page_buffers (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_end_fn ; 

__attribute__((used)) static int ext3_journalled_writepage(struct page *page,
				struct writeback_control *wbc)
{
	struct inode *inode = page->mapping->host;
	handle_t *handle = NULL;
	int ret = 0;
	int err;

	if (ext3_journal_current_handle())
		goto no_write;

	trace_ext3_journalled_writepage(page);
	handle = ext3_journal_start(inode, ext3_writepage_trans_blocks(inode));
	if (IS_ERR(handle)) {
		ret = PTR_ERR(handle);
		goto no_write;
	}

	if (!page_has_buffers(page) || PageChecked(page)) {
		/*
		 * It's mmapped pagecache.  Add buffers and journal it.  There
		 * doesn't seem much point in redirtying the page here.
		 */
		ClearPageChecked(page);
		ret = block_prepare_write(page, 0, PAGE_CACHE_SIZE,
					ext3_journalled_get_block);
		if (ret != 0) {
			ext3_journal_stop(handle);
			goto out_unlock;
		}
		ret = walk_page_buffers(handle, page_buffers(page), 0,
			PAGE_CACHE_SIZE, NULL, do_journal_get_write_access);

		err = walk_page_buffers(handle, page_buffers(page), 0,
				PAGE_CACHE_SIZE, NULL, write_end_fn);
		if (ret == 0)
			ret = err;
		EXT3_I(inode)->i_state |= EXT3_STATE_JDATA;
		unlock_page(page);
	} else {
		/*
		 * It may be a page full of checkpoint-mode buffers.  We don't
		 * really know unless we go poke around in the buffer_heads.
		 * But block_write_full_page will do the right thing.
		 */
		ret = block_write_full_page(page, ext3_get_block, wbc);
	}
	err = ext3_journal_stop(handle);
	if (!ret)
		ret = err;
out:
	return ret;

no_write:
	redirty_page_for_writepage(wbc, page);
out_unlock:
	unlock_page(page);
	goto out;
}