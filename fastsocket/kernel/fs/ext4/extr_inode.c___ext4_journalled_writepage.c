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
struct writeback_control {int dummy; } ;
struct page {struct address_space* mapping; } ;
struct inode {int dummy; } ;
struct buffer_head {int dummy; } ;
struct address_space {struct inode* host; } ;
typedef  int /*<<< orphan*/  handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  EXT4_STATE_JDATA ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bget_one ; 
 int /*<<< orphan*/  bput_one ; 
 int /*<<< orphan*/  do_journal_get_write_access ; 
 int /*<<< orphan*/ * ext4_journal_start (struct inode*,int /*<<< orphan*/ ) ; 
 int ext4_journal_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ext4_set_inode_state (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_writepage_trans_blocks (struct inode*) ; 
 struct buffer_head* page_buffers (struct page*) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 
 int walk_page_buffers (int /*<<< orphan*/ *,struct buffer_head*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_end_fn ; 

__attribute__((used)) static int __ext4_journalled_writepage(struct page *page,
				       struct writeback_control *wbc,
				       unsigned int len)
{
	struct address_space *mapping = page->mapping;
	struct inode *inode = mapping->host;
	struct buffer_head *page_bufs;
	handle_t *handle = NULL;
	int ret = 0;
	int err;

	page_bufs = page_buffers(page);
	BUG_ON(!page_bufs);
	walk_page_buffers(handle, page_bufs, 0, len, NULL, bget_one);
	/* As soon as we unlock the page, it can go away, but we have
	 * references to buffers so we are safe */
	unlock_page(page);

	handle = ext4_journal_start(inode, ext4_writepage_trans_blocks(inode));
	if (IS_ERR(handle)) {
		ret = PTR_ERR(handle);
		goto out;
	}

	ret = walk_page_buffers(handle, page_bufs, 0, len, NULL,
				do_journal_get_write_access);

	err = walk_page_buffers(handle, page_bufs, 0, len, NULL,
				write_end_fn);
	if (ret == 0)
		ret = err;
	err = ext4_journal_stop(handle);
	if (!ret)
		ret = err;

	walk_page_buffers(handle, page_bufs, 0, len, NULL, bput_one);
	ext4_set_inode_state(inode, EXT4_STATE_JDATA);
out:
	return ret;
}