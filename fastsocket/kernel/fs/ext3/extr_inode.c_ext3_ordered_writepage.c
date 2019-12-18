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
struct inode {TYPE_2__* i_sb; } ;
struct buffer_head {int dummy; } ;
typedef  int /*<<< orphan*/  handle_t ;
struct TYPE_4__ {int /*<<< orphan*/  s_blocksize; } ;
struct TYPE_3__ {struct inode* host; } ;

/* Variables and functions */
 int BH_Dirty ; 
 int BH_Uptodate ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  J_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PAGE_CACHE_SIZE ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PageLocked (struct page*) ; 
 int /*<<< orphan*/  bget_one ; 
 int block_write_full_page (struct page*,int /*<<< orphan*/ *,struct writeback_control*) ; 
 int /*<<< orphan*/  bput_one ; 
 int /*<<< orphan*/  buffer_unmapped ; 
 int /*<<< orphan*/  create_empty_buffers (struct page*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * ext3_get_block ; 
 scalar_t__ ext3_journal_current_handle () ; 
 int /*<<< orphan*/ * ext3_journal_start (struct inode*,int /*<<< orphan*/ ) ; 
 int ext3_journal_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ext3_writepage_trans_blocks (struct inode*) ; 
 int /*<<< orphan*/  journal_dirty_data_fn ; 
 struct buffer_head* page_buffers (struct page*) ; 
 int /*<<< orphan*/  page_has_buffers (struct page*) ; 
 int /*<<< orphan*/  redirty_page_for_writepage (struct writeback_control*,struct page*) ; 
 int /*<<< orphan*/  trace_ext3_ordered_writepage (struct page*) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 
 int walk_page_buffers (int /*<<< orphan*/ *,struct buffer_head*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ext3_ordered_writepage(struct page *page,
				struct writeback_control *wbc)
{
	struct inode *inode = page->mapping->host;
	struct buffer_head *page_bufs;
	handle_t *handle = NULL;
	int ret = 0;
	int err;

	J_ASSERT(PageLocked(page));

	/*
	 * We give up here if we're reentered, because it might be for a
	 * different filesystem.
	 */
	if (ext3_journal_current_handle())
		goto out_fail;

	trace_ext3_ordered_writepage(page);
	if (!page_has_buffers(page)) {
		create_empty_buffers(page, inode->i_sb->s_blocksize,
				(1 << BH_Dirty)|(1 << BH_Uptodate));
		page_bufs = page_buffers(page);
	} else {
		page_bufs = page_buffers(page);
		if (!walk_page_buffers(NULL, page_bufs, 0, PAGE_CACHE_SIZE,
				       NULL, buffer_unmapped)) {
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

	walk_page_buffers(handle, page_bufs, 0,
			PAGE_CACHE_SIZE, NULL, bget_one);

	ret = block_write_full_page(page, ext3_get_block, wbc);

	/*
	 * The page can become unlocked at any point now, and
	 * truncate can then come in and change things.  So we
	 * can't touch *page from now on.  But *page_bufs is
	 * safe due to elevated refcount.
	 */

	/*
	 * And attach them to the current transaction.  But only if
	 * block_write_full_page() succeeded.  Otherwise they are unmapped,
	 * and generally junk.
	 */
	if (ret == 0) {
		err = walk_page_buffers(handle, page_bufs, 0, PAGE_CACHE_SIZE,
					NULL, journal_dirty_data_fn);
		if (!ret)
			ret = err;
	}
	walk_page_buffers(handle, page_bufs, 0,
			PAGE_CACHE_SIZE, NULL, bput_one);
	err = ext3_journal_stop(handle);
	if (!ret)
		ret = err;
	return ret;

out_fail:
	redirty_page_for_writepage(wbc, page);
	unlock_page(page);
	return ret;
}