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
 unsigned int AOP_FLAG_NOFS ; 
 int ENOMEM ; 
 int ENOSPC ; 
 scalar_t__ FALL_BACK_TO_NONDELALLOC ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PAGE_CACHE_SHIFT ; 
 int PAGE_CACHE_SIZE ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int block_write_begin (struct file*,struct address_space*,int,unsigned int,unsigned int,struct page**,void**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_da_get_block_prep ; 
 int /*<<< orphan*/ * ext4_journal_start (struct inode*,int) ; 
 int /*<<< orphan*/  ext4_journal_stop (int /*<<< orphan*/ *) ; 
 scalar_t__ ext4_nonda_switch (int /*<<< orphan*/ ) ; 
 scalar_t__ ext4_should_retry_alloc (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  ext4_truncate_failed_write (struct inode*) ; 
 int ext4_write_begin (struct file*,struct address_space*,int,unsigned int,unsigned int,struct page**,void**) ; 
 struct page* grab_cache_page_write_begin (struct address_space*,int,unsigned int) ; 
 int /*<<< orphan*/  page_cache_release (struct page*) ; 
 int /*<<< orphan*/  trace_ext4_da_write_begin (struct inode*,int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

__attribute__((used)) static int ext4_da_write_begin(struct file *file, struct address_space *mapping,
			       loff_t pos, unsigned len, unsigned flags,
			       struct page **pagep, void **fsdata)
{
	int ret, retries = 0;
	struct page *page;
	pgoff_t index;
	unsigned from, to;
	struct inode *inode = mapping->host;
	handle_t *handle;

	index = pos >> PAGE_CACHE_SHIFT;
	from = pos & (PAGE_CACHE_SIZE - 1);
	to = from + len;

	if (ext4_nonda_switch(inode->i_sb)) {
		*fsdata = (void *)FALL_BACK_TO_NONDELALLOC;
		return ext4_write_begin(file, mapping, pos,
					len, flags, pagep, fsdata);
	}
	*fsdata = (void *)0;
	trace_ext4_da_write_begin(inode, pos, len, flags);
retry:
	/*
	 * With delayed allocation, we don't log the i_disksize update
	 * if there is delayed block allocation. But we still need
	 * to journalling the i_disksize update if writes to the end
	 * of file which has an already mapped buffer.
	 */
	handle = ext4_journal_start(inode, 1);
	if (IS_ERR(handle)) {
		ret = PTR_ERR(handle);
		goto out;
	}
	/* We cannot recurse into the filesystem as the transaction is already
	 * started */
	flags |= AOP_FLAG_NOFS;

	page = grab_cache_page_write_begin(mapping, index, flags);
	if (!page) {
		ext4_journal_stop(handle);
		ret = -ENOMEM;
		goto out;
	}
	*pagep = page;

	ret = block_write_begin(file, mapping, pos, len, flags, pagep, fsdata,
				ext4_da_get_block_prep);
	if (ret < 0) {
		unlock_page(page);
		ext4_journal_stop(handle);
		page_cache_release(page);
		/*
		 * block_write_begin may have instantiated a few blocks
		 * outside i_size.  Trim these off again. Don't need
		 * i_size_read because we hold i_mutex.
		 */
		if (pos + len > inode->i_size)
			ext4_truncate_failed_write(inode);
	}

	if (ret == -ENOSPC && ext4_should_retry_alloc(inode->i_sb, &retries))
		goto retry;
out:
	return ret;
}