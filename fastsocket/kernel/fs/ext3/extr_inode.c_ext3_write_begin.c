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
struct inode {int i_size; int /*<<< orphan*/  i_sb; } ;
struct file {int dummy; } ;
struct address_space {struct inode* host; } ;
typedef  int pgoff_t ;
typedef  int loff_t ;
typedef  int /*<<< orphan*/  handle_t ;

/* Variables and functions */
 int ENOMEM ; 
 int ENOSPC ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PAGE_CACHE_SHIFT ; 
 int PAGE_CACHE_SIZE ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int block_write_begin (struct file*,struct address_space*,int,unsigned int,unsigned int,struct page**,void**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_journal_get_write_access ; 
 scalar_t__ ext3_can_truncate (struct inode*) ; 
 int /*<<< orphan*/  ext3_get_block ; 
 int /*<<< orphan*/ * ext3_journal_start (struct inode*,int) ; 
 int /*<<< orphan*/  ext3_journal_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ext3_journalled_get_block ; 
 int /*<<< orphan*/  ext3_orphan_add (int /*<<< orphan*/ *,struct inode*) ; 
 scalar_t__ ext3_should_journal_data (struct inode*) ; 
 scalar_t__ ext3_should_retry_alloc (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  ext3_truncate_failed_write (struct inode*) ; 
 int ext3_writepage_trans_blocks (struct inode*) ; 
 struct page* grab_cache_page_write_begin (struct address_space*,int,unsigned int) ; 
 int /*<<< orphan*/  page_buffers (struct page*) ; 
 int /*<<< orphan*/  page_cache_release (struct page*) ; 
 int /*<<< orphan*/  trace_ext3_write_begin (struct inode*,int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 
 int walk_page_buffers (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ext3_write_begin(struct file *file, struct address_space *mapping,
				loff_t pos, unsigned len, unsigned flags,
				struct page **pagep, void **fsdata)
{
	struct inode *inode = mapping->host;
	int ret;
	handle_t *handle;
	int retries = 0;
	struct page *page;
	pgoff_t index;
	unsigned from, to;
	/* Reserve one block more for addition to orphan list in case
	 * we allocate blocks but write fails for some reason */
	int needed_blocks = ext3_writepage_trans_blocks(inode) + 1;

	trace_ext3_write_begin(inode, pos, len, flags);

	index = pos >> PAGE_CACHE_SHIFT;
	from = pos & (PAGE_CACHE_SIZE - 1);
	to = from + len;

retry:
	page = grab_cache_page_write_begin(mapping, index, flags);
	if (!page)
		return -ENOMEM;
	*pagep = page;

	handle = ext3_journal_start(inode, needed_blocks);
	if (IS_ERR(handle)) {
		unlock_page(page);
		page_cache_release(page);
		ret = PTR_ERR(handle);
		goto out;
	}
	if (ext3_should_journal_data(inode)) {
		ret = block_write_begin(file, mapping, pos, len, flags, pagep,
					fsdata, ext3_journalled_get_block);
		if (ret)
			goto write_begin_failed;
		ret = walk_page_buffers(handle, page_buffers(page), from, to,
					NULL, do_journal_get_write_access);
	} else {
		ret = block_write_begin(file, mapping, pos, len, flags, pagep,
					fsdata, ext3_get_block);
	}

write_begin_failed:
	if (ret) {
		/*
		 * block_write_begin may have instantiated a few blocks
		 * outside i_size.  Trim these off again. Don't need
		 * i_size_read because we hold i_mutex.
		 *
		 * Add inode to orphan list in case we crash before truncate
		 * finishes. Do this only if ext3_can_truncate() agrees so
		 * that orphan processing code is happy.
		 */
		if (pos + len > inode->i_size && ext3_can_truncate(inode))
			ext3_orphan_add(handle, inode);
		ext3_journal_stop(handle);
		unlock_page(page);
		page_cache_release(page);
		if (pos + len > inode->i_size)
			ext3_truncate_failed_write(inode);
	}
	if (ret == -ENOSPC && ext3_should_retry_alloc(inode->i_sb, &retries))
		goto retry;
out:
	return ret;
}