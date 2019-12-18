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
struct page {int index; } ;
struct inode {TYPE_1__* i_sb; } ;
struct buffer_head {struct buffer_head* b_this_page; int /*<<< orphan*/ * b_bdev; } ;
typedef  int loff_t ;
typedef  int /*<<< orphan*/  handle_t ;
typedef  int ext4_lblk_t ;
typedef  int ext4_fsblk_t ;
struct TYPE_2__ {unsigned int s_blocksize; int s_blocksize_bits; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUFFER_TRACE (struct buffer_head*,char*) ; 
 int EINVAL ; 
 int EIO ; 
 int EXT4_DISCARD_PARTIAL_PG_ZERO_UNMAPPED ; 
 int PAGE_CACHE_SHIFT ; 
 int PAGE_CACHE_SIZE ; 
 scalar_t__ PageUptodate (struct page*) ; 
 int /*<<< orphan*/  READ ; 
 scalar_t__ buffer_mapped (struct buffer_head*) ; 
 int /*<<< orphan*/  buffer_uptodate (struct buffer_head*) ; 
 int /*<<< orphan*/  clear_buffer_delay (struct buffer_head*) ; 
 int /*<<< orphan*/  clear_buffer_dirty (struct buffer_head*) ; 
 int /*<<< orphan*/  clear_buffer_mapped (struct buffer_head*) ; 
 int /*<<< orphan*/  clear_buffer_new (struct buffer_head*) ; 
 int /*<<< orphan*/  clear_buffer_req (struct buffer_head*) ; 
 int /*<<< orphan*/  clear_buffer_unwritten (struct buffer_head*) ; 
 int /*<<< orphan*/  clear_buffer_uptodate (struct buffer_head*) ; 
 int /*<<< orphan*/  create_empty_buffers (struct page*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_get_block (struct inode*,int,struct buffer_head*,int /*<<< orphan*/ ) ; 
 int ext4_handle_dirty_metadata (int /*<<< orphan*/ *,struct inode*,struct buffer_head*) ; 
 int ext4_journal_get_write_access (int /*<<< orphan*/ *,struct buffer_head*) ; 
 scalar_t__ ext4_should_journal_data (struct inode*) ; 
 int /*<<< orphan*/  ll_rw_block (int /*<<< orphan*/ ,int,struct buffer_head**) ; 
 int /*<<< orphan*/  mark_buffer_dirty (struct buffer_head*) ; 
 struct buffer_head* page_buffers (struct page*) ; 
 int /*<<< orphan*/  page_has_buffers (struct page*) ; 
 int /*<<< orphan*/  set_buffer_uptodate (struct buffer_head*) ; 
 int /*<<< orphan*/  wait_on_buffer (struct buffer_head*) ; 
 int /*<<< orphan*/  zero_user (struct page*,unsigned int,unsigned int) ; 

int ext4_discard_partial_page_buffers_no_lock(handle_t *handle,
		struct inode *inode, struct page *page, loff_t from,
		loff_t length, int flags)
{
	ext4_fsblk_t index = from >> PAGE_CACHE_SHIFT;
	unsigned int offset = from & (PAGE_CACHE_SIZE-1);
	unsigned int blocksize, max, pos;
	ext4_lblk_t iblock;
	struct buffer_head *bh;
	int err = 0;

	blocksize = inode->i_sb->s_blocksize;
	max = PAGE_CACHE_SIZE - offset;

	if (index != page->index)
		return -EINVAL;

	/*
	 * correct length if it does not fall between
	 * 'from' and the end of the page
	 */
	if (length > max || length < 0)
		length = max;

	iblock = index << (PAGE_CACHE_SHIFT - inode->i_sb->s_blocksize_bits);

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

	pos = offset;
	while (pos < offset + length) {
		unsigned int end_of_block, range_to_discard;

		err = 0;

		/* The length of space left to zero and unmap */
		range_to_discard = offset + length - pos;

		/* The length of space until the end of the block */
		end_of_block = blocksize - (pos & (blocksize-1));

		/*
		 * Do not unmap or zero past end of block
		 * for this buffer head
		 */
		if (range_to_discard > end_of_block)
			range_to_discard = end_of_block;


		/*
		 * Skip this buffer head if we are only zeroing unampped
		 * regions of the page
		 */
		if (flags & EXT4_DISCARD_PARTIAL_PG_ZERO_UNMAPPED &&
			buffer_mapped(bh))
				goto next;

		/* If the range is block aligned, unmap */
		if (range_to_discard == blocksize) {
			clear_buffer_dirty(bh);
			bh->b_bdev = NULL;
			clear_buffer_mapped(bh);
			clear_buffer_req(bh);
			clear_buffer_new(bh);
			clear_buffer_delay(bh);
			clear_buffer_unwritten(bh);
			clear_buffer_uptodate(bh);
			zero_user(page, pos, range_to_discard);
			BUFFER_TRACE(bh, "Buffer discarded");
			goto next;
		}

		/*
		 * If this block is not completely contained in the range
		 * to be discarded, then it is not going to be released. Because
		 * we need to keep this block, we need to make sure this part
		 * of the page is uptodate before we modify it by writeing
		 * partial zeros on it.
		 */
		if (!buffer_mapped(bh)) {
			/*
			 * Buffer head must be mapped before we can read
			 * from the block
			 */
			BUFFER_TRACE(bh, "unmapped");
			ext4_get_block(inode, iblock, bh, 0);
			/* unmapped? It's a hole - nothing to do */
			if (!buffer_mapped(bh)) {
				BUFFER_TRACE(bh, "still unmapped");
				goto next;
			}
		}

		/* Ok, it's mapped. Make sure it's up-to-date */
		if (PageUptodate(page))
			set_buffer_uptodate(bh);

		if (!buffer_uptodate(bh)) {
			err = -EIO;
			ll_rw_block(READ, 1, &bh);
			wait_on_buffer(bh);
			/* Uhhuh. Read error. Complain and punt.*/
			if (!buffer_uptodate(bh))
				goto next;
		}

		if (ext4_should_journal_data(inode)) {
			BUFFER_TRACE(bh, "get write access");
			err = ext4_journal_get_write_access(handle, bh);
			if (err)
				goto next;
		}

		zero_user(page, pos, range_to_discard);

		err = 0;
		if (ext4_should_journal_data(inode)) {
			err = ext4_handle_dirty_metadata(handle, inode, bh);
		} else
			mark_buffer_dirty(bh);

		BUFFER_TRACE(bh, "Partial buffer zeroed");
next:
		bh = bh->b_this_page;
		iblock++;
		pos += range_to_discard;
	}

	return err;
}