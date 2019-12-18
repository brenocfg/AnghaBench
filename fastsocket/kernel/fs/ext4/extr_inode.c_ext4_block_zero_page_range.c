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
struct page {int dummy; } ;
struct inode {TYPE_1__* i_sb; } ;
struct buffer_head {struct buffer_head* b_this_page; } ;
struct address_space {struct inode* host; } ;
typedef  int loff_t ;
typedef  int /*<<< orphan*/  handle_t ;
typedef  int ext4_lblk_t ;
typedef  int ext4_fsblk_t ;
struct TYPE_2__ {unsigned int s_blocksize; int s_blocksize_bits; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUFFER_TRACE (struct buffer_head*,char*) ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  NOBH ; 
 int PAGE_CACHE_SHIFT ; 
 int PAGE_CACHE_SIZE ; 
 scalar_t__ PageUptodate (struct page*) ; 
 int /*<<< orphan*/  READ ; 
 int __GFP_FS ; 
 scalar_t__ buffer_freed (struct buffer_head*) ; 
 int /*<<< orphan*/  buffer_mapped (struct buffer_head*) ; 
 int /*<<< orphan*/  buffer_uptodate (struct buffer_head*) ; 
 int /*<<< orphan*/  create_empty_buffers (struct page*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_get_block (struct inode*,int,struct buffer_head*,int /*<<< orphan*/ ) ; 
 int ext4_handle_dirty_metadata (int /*<<< orphan*/ *,struct inode*,struct buffer_head*) ; 
 int ext4_journal_get_write_access (int /*<<< orphan*/ *,struct buffer_head*) ; 
 scalar_t__ ext4_should_journal_data (struct inode*) ; 
 scalar_t__ ext4_should_writeback_data (struct inode*) ; 
 struct page* find_or_create_page (struct address_space*,int,int) ; 
 int /*<<< orphan*/  ll_rw_block (int /*<<< orphan*/ ,int,struct buffer_head**) ; 
 int mapping_gfp_mask (struct address_space*) ; 
 int /*<<< orphan*/  mark_buffer_dirty (struct buffer_head*) ; 
 struct buffer_head* page_buffers (struct page*) ; 
 int /*<<< orphan*/  page_cache_release (struct page*) ; 
 int /*<<< orphan*/  page_has_buffers (struct page*) ; 
 int /*<<< orphan*/  set_buffer_uptodate (struct buffer_head*) ; 
 int /*<<< orphan*/  set_page_dirty (struct page*) ; 
 scalar_t__ test_opt (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 
 int /*<<< orphan*/  wait_on_buffer (struct buffer_head*) ; 
 int /*<<< orphan*/  zero_user (struct page*,unsigned int,int) ; 

int ext4_block_zero_page_range(handle_t *handle,
		struct address_space *mapping, loff_t from, loff_t length)
{
	ext4_fsblk_t index = from >> PAGE_CACHE_SHIFT;
	unsigned offset = from & (PAGE_CACHE_SIZE-1);
	unsigned blocksize, max, pos;
	ext4_lblk_t iblock;
	struct inode *inode = mapping->host;
	struct buffer_head *bh;
	struct page *page;
	int err = 0;

	page = find_or_create_page(mapping, from >> PAGE_CACHE_SHIFT,
				   mapping_gfp_mask(mapping) & ~__GFP_FS);
	if (!page)
		return -ENOMEM;

	blocksize = inode->i_sb->s_blocksize;
	max = blocksize - (offset & (blocksize - 1));

	/*
	 * correct length if it does not fall between
	 * 'from' and the end of the block
	 */
	if (length > max || length < 0)
		length = max;

	iblock = index << (PAGE_CACHE_SHIFT - inode->i_sb->s_blocksize_bits);

	/*
	 * For "nobh" option,  we can only work if we don't need to
	 * read-in the page - otherwise we create buffers to do the IO.
	 */
	if (!page_has_buffers(page) && test_opt(inode->i_sb, NOBH) &&
	     ext4_should_writeback_data(inode) && PageUptodate(page)) {
		zero_user(page, offset, length);
		set_page_dirty(page);
		goto unlock;
	}

	if (!page_has_buffers(page))
		create_empty_buffers(page, blocksize, 0);

	/* Find the buffer that contains "offset" */
	bh = page_buffers(page);
	pos = blocksize;
	while (offset >= pos) {
		bh = bh->b_this_page;
		iblock++;
		pos += blocksize;
	}

	err = 0;
	if (buffer_freed(bh)) {
		BUFFER_TRACE(bh, "freed: skip");
		goto unlock;
	}

	if (!buffer_mapped(bh)) {
		BUFFER_TRACE(bh, "unmapped");
		ext4_get_block(inode, iblock, bh, 0);
		/* unmapped? It's a hole - nothing to do */
		if (!buffer_mapped(bh)) {
			BUFFER_TRACE(bh, "still unmapped");
			goto unlock;
		}
	}

	/* Ok, it's mapped. Make sure it's up-to-date */
	if (PageUptodate(page))
		set_buffer_uptodate(bh);

	if (!buffer_uptodate(bh)) {
		err = -EIO;
		ll_rw_block(READ, 1, &bh);
		wait_on_buffer(bh);
		/* Uhhuh. Read error. Complain and punt. */
		if (!buffer_uptodate(bh))
			goto unlock;
	}

	if (ext4_should_journal_data(inode)) {
		BUFFER_TRACE(bh, "get write access");
		err = ext4_journal_get_write_access(handle, bh);
		if (err)
			goto unlock;
	}

	zero_user(page, offset, length);

	BUFFER_TRACE(bh, "zeroed end of block");

	err = 0;
	if (ext4_should_journal_data(inode)) {
		err = ext4_handle_dirty_metadata(handle, inode, bh);
	} else
		mark_buffer_dirty(bh);

unlock:
	unlock_page(page);
	page_cache_release(page);
	return err;
}