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
struct super_block {int s_blocksize; } ;
struct inode {int i_size; int /*<<< orphan*/  i_mutex; int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_mtime; struct address_space* i_mapping; struct super_block* i_sb; } ;
struct address_space {scalar_t__ nrpages; } ;
typedef  int loff_t ;
typedef  int /*<<< orphan*/  handle_t ;
typedef  int ext4_lblk_t ;
struct TYPE_2__ {int /*<<< orphan*/  i_data_sem; } ;

/* Variables and functions */
 int EPERM ; 
 int ETXTBSY ; 
 int EXT4_BLOCK_SIZE_BITS (struct super_block*) ; 
 TYPE_1__* EXT4_I (struct inode*) ; 
 scalar_t__ IS_APPEND (struct inode*) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_IMMUTABLE (struct inode*) ; 
 scalar_t__ IS_SWAPFILE (struct inode*) ; 
 scalar_t__ IS_SYNC (struct inode*) ; 
 int /*<<< orphan*/  PAGECACHE_TAG_DIRTY ; 
 int PAGE_CACHE_SHIFT ; 
 int PAGE_CACHE_SIZE ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ext4_current_time (struct inode*) ; 
 int ext4_discard_partial_page_buffers (int /*<<< orphan*/ *,struct address_space*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_discard_preallocations (struct inode*) ; 
 int /*<<< orphan*/  ext4_ext_invalidate_cache (struct inode*) ; 
 int ext4_ext_remove_space (struct inode*,int,int) ; 
 int /*<<< orphan*/  ext4_handle_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ext4_journal_start (struct inode*,int) ; 
 int /*<<< orphan*/  ext4_journal_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ext4_mark_inode_dirty (int /*<<< orphan*/ *,struct inode*) ; 
 int ext4_orphan_add (int /*<<< orphan*/ *,struct inode*) ; 
 int /*<<< orphan*/  ext4_orphan_del (int /*<<< orphan*/ *,struct inode*) ; 
 int ext4_writepage_trans_blocks (struct inode*) ; 
 int filemap_write_and_wait_range (struct address_space*,int,int) ; 
 int flush_aio_dio_completed_IO (struct inode*) ; 
 scalar_t__ mapping_tagged (struct address_space*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  truncate_pagecache_range (struct inode*,int,int) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

int ext4_ext_punch_hole(struct inode *inode, loff_t offset, loff_t length)
{
	struct super_block *sb = inode->i_sb;
	ext4_lblk_t first_block, stop_block;
	struct address_space *mapping = inode->i_mapping;
	handle_t *handle;
	loff_t first_page, last_page, page_len;
	loff_t first_page_offset, last_page_offset;
	int credits, err = 0;

	/*
	 * Write out all dirty pages to avoid race conditions
	 * Then release them.
	 */
	if (mapping->nrpages && mapping_tagged(mapping, PAGECACHE_TAG_DIRTY)) {
		err = filemap_write_and_wait_range(mapping,
			offset, offset + length - 1);

		if (err)
			return err;
	}

	mutex_lock(&inode->i_mutex);
	/* It's not possible punch hole on append only file */
	if (IS_APPEND(inode) || IS_IMMUTABLE(inode)) {
		err = -EPERM;
		goto out_mutex;
	}
	if (IS_SWAPFILE(inode)) {
		err = -ETXTBSY;
		goto out_mutex;
	}

	/* No need to punch hole beyond i_size */
	if (offset >= inode->i_size)
		goto out_mutex;

	/*
	 * If the hole extends beyond i_size, set the hole
	 * to end after the page that contains i_size
	 */
	if (offset + length > inode->i_size) {
		length = inode->i_size +
		   PAGE_CACHE_SIZE - (inode->i_size & (PAGE_CACHE_SIZE - 1)) -
		   offset;
	}

	first_page = (offset + PAGE_CACHE_SIZE - 1) >> PAGE_CACHE_SHIFT;
	last_page = (offset + length) >> PAGE_CACHE_SHIFT;

	first_page_offset = first_page << PAGE_CACHE_SHIFT;
	last_page_offset = last_page << PAGE_CACHE_SHIFT;

	/* Now release the pages */
	if (last_page_offset > first_page_offset) {
		truncate_pagecache_range(inode, first_page_offset,
					 last_page_offset - 1);
	}

	/* finish any pending end_io work */
	err = flush_aio_dio_completed_IO(inode);
	if (err)
		goto out_mutex;

	credits = ext4_writepage_trans_blocks(inode);
	handle = ext4_journal_start(inode, credits);
	if (IS_ERR(handle)) {
		err = PTR_ERR(handle);
		goto out_mutex;
	}

	err = ext4_orphan_add(handle, inode);
	if (err)
		goto out;

	/*
	 * Now we need to zero out the non-page-aligned data in the
	 * pages at the start and tail of the hole, and unmap the buffer
	 * heads for the block aligned regions of the page that were
	 * completely zeroed.
	 */
	if (first_page > last_page) {
		/*
		 * If the file space being truncated is contained within a page
		 * just zero out and unmap the middle of that page
		 */
		err = ext4_discard_partial_page_buffers(handle,
			mapping, offset, length, 0);

		if (err)
			goto out;
	} else {
		/*
		 * zero out and unmap the partial page that contains
		 * the start of the hole
		 */
		page_len  = first_page_offset - offset;
		if (page_len > 0) {
			err = ext4_discard_partial_page_buffers(handle, mapping,
						   offset, page_len, 0);
			if (err)
				goto out;
		}

		/*
		 * zero out and unmap the partial page that contains
		 * the end of the hole
		 */
		page_len = offset + length - last_page_offset;
		if (page_len > 0) {
			err = ext4_discard_partial_page_buffers(handle, mapping,
					last_page_offset, page_len, 0);
			if (err)
				goto out;
		}
	}

	/*
	 * If i_size is contained in the last page, we need to
	 * unmap and zero the partial page after i_size
	 */
	if (inode->i_size >> PAGE_CACHE_SHIFT == last_page &&
	   inode->i_size % PAGE_CACHE_SIZE != 0) {

		page_len = PAGE_CACHE_SIZE -
			(inode->i_size & (PAGE_CACHE_SIZE - 1));

		if (page_len > 0) {
			err = ext4_discard_partial_page_buffers(handle,
			  mapping, inode->i_size, page_len, 0);

			if (err)
				goto out;
		}
	}

	first_block = (offset + sb->s_blocksize - 1) >>
		EXT4_BLOCK_SIZE_BITS(sb);
	stop_block = (offset + length) >> EXT4_BLOCK_SIZE_BITS(sb);

	/* If there are no blocks to remove, return now */
	if (first_block >= stop_block)
		goto out;

	down_write(&EXT4_I(inode)->i_data_sem);
	ext4_ext_invalidate_cache(inode);
	ext4_discard_preallocations(inode);

	err = ext4_ext_remove_space(inode, first_block, stop_block - 1);

	ext4_ext_invalidate_cache(inode);
	ext4_discard_preallocations(inode);

	if (IS_SYNC(inode))
		ext4_handle_sync(handle);

	up_write(&EXT4_I(inode)->i_data_sem);

out:
	ext4_orphan_del(handle, inode);
	inode->i_mtime = inode->i_ctime = ext4_current_time(inode);
	ext4_mark_inode_dirty(handle, inode);
	ext4_journal_stop(handle);
out_mutex:
	mutex_unlock(&inode->i_mutex);
	return err;
}