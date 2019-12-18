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
struct writeback_control {scalar_t__ sync_mode; int /*<<< orphan*/  nonblocking; } ;
struct super_block {int s_blocksize; unsigned long s_blocksize_bits; } ;
struct reiserfs_transaction_handle {scalar_t__ t_trans_id; } ;
struct page {unsigned long index; TYPE_1__* mapping; } ;
struct inode {unsigned long i_size; int i_blkbits; struct super_block* i_sb; } ;
struct buffer_head {scalar_t__ b_blocknr; struct buffer_head* b_this_page; } ;
typedef  unsigned long sector_t ;
struct TYPE_4__ {int flags; } ;
struct TYPE_3__ {struct inode* host; } ;

/* Variables and functions */
 int BH_Dirty ; 
 int BH_Uptodate ; 
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ClearPageChecked (struct page*) ; 
 int /*<<< orphan*/  ClearPageUptodate (struct page*) ; 
 unsigned long PAGE_CACHE_SHIFT ; 
 int PAGE_CACHE_SIZE ; 
 int PF_MEMALLOC ; 
 int PageChecked (struct page*) ; 
 int /*<<< orphan*/  PageWriteback (struct page*) ; 
 int /*<<< orphan*/  SetPageError (struct page*) ; 
 int /*<<< orphan*/  SetPageUptodate (struct page*) ; 
 scalar_t__ WB_SYNC_NONE ; 
 int /*<<< orphan*/  WRITE ; 
 scalar_t__ buffer_async_write (struct buffer_head*) ; 
 scalar_t__ buffer_dirty (struct buffer_head*) ; 
 scalar_t__ buffer_mapped (struct buffer_head*) ; 
 int /*<<< orphan*/  buffer_uptodate (struct buffer_head*) ; 
 int /*<<< orphan*/  clear_buffer_dirty (struct buffer_head*) ; 
 int /*<<< orphan*/  create_empty_buffers (struct page*,int,int) ; 
 TYPE_2__* current ; 
 int /*<<< orphan*/  end_page_writeback (struct page*) ; 
 int /*<<< orphan*/  get_bh (struct buffer_head*) ; 
 int i_size_read (struct inode*) ; 
 int journal_begin (struct reiserfs_transaction_handle*,struct super_block*,int) ; 
 int journal_end (struct reiserfs_transaction_handle*,struct super_block*,int) ; 
 int /*<<< orphan*/  journal_mark_dirty (struct reiserfs_transaction_handle*,struct super_block*,struct buffer_head*) ; 
 int /*<<< orphan*/  lock_buffer (struct buffer_head*) ; 
 int map_block_for_writepage (struct inode*,struct buffer_head*,unsigned long) ; 
 int /*<<< orphan*/  mark_buffer_async_write (struct buffer_head*) ; 
 struct buffer_head* page_buffers (struct page*) ; 
 int /*<<< orphan*/  page_has_buffers (struct page*) ; 
 int /*<<< orphan*/  put_bh (struct buffer_head*) ; 
 int /*<<< orphan*/  redirty_page_for_writepage (struct writeback_control*,struct page*) ; 
 int /*<<< orphan*/  reiserfs_prepare_for_journal (struct super_block*,struct buffer_head*,int) ; 
 int /*<<< orphan*/  reiserfs_update_inode_transaction (struct inode*) ; 
 int /*<<< orphan*/  reiserfs_write_lock (struct super_block*) ; 
 int /*<<< orphan*/  reiserfs_write_unlock (struct super_block*) ; 
 int /*<<< orphan*/  set_buffer_uptodate (struct buffer_head*) ; 
 int /*<<< orphan*/  set_page_writeback (struct page*) ; 
 int /*<<< orphan*/  submit_bh (int /*<<< orphan*/ ,struct buffer_head*) ; 
 scalar_t__ test_clear_buffer_dirty (struct buffer_head*) ; 
 int /*<<< orphan*/  trylock_buffer (struct buffer_head*) ; 
 int /*<<< orphan*/  unlock_buffer (struct buffer_head*) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 
 int /*<<< orphan*/  zero_user_segment (struct page*,unsigned int,int) ; 

__attribute__((used)) static int reiserfs_write_full_page(struct page *page,
				    struct writeback_control *wbc)
{
	struct inode *inode = page->mapping->host;
	unsigned long end_index = inode->i_size >> PAGE_CACHE_SHIFT;
	int error = 0;
	unsigned long block;
	sector_t last_block;
	struct buffer_head *head, *bh;
	int partial = 0;
	int nr = 0;
	int checked = PageChecked(page);
	struct reiserfs_transaction_handle th;
	struct super_block *s = inode->i_sb;
	int bh_per_page = PAGE_CACHE_SIZE / s->s_blocksize;
	th.t_trans_id = 0;

	/* no logging allowed when nonblocking or from PF_MEMALLOC */
	if (checked && (current->flags & PF_MEMALLOC)) {
		redirty_page_for_writepage(wbc, page);
		unlock_page(page);
		return 0;
	}

	/* The page dirty bit is cleared before writepage is called, which
	 * means we have to tell create_empty_buffers to make dirty buffers
	 * The page really should be up to date at this point, so tossing
	 * in the BH_Uptodate is just a sanity check.
	 */
	if (!page_has_buffers(page)) {
		create_empty_buffers(page, s->s_blocksize,
				     (1 << BH_Dirty) | (1 << BH_Uptodate));
	}
	head = page_buffers(page);

	/* last page in the file, zero out any contents past the
	 ** last byte in the file
	 */
	if (page->index >= end_index) {
		unsigned last_offset;

		last_offset = inode->i_size & (PAGE_CACHE_SIZE - 1);
		/* no file contents in this page */
		if (page->index >= end_index + 1 || !last_offset) {
			unlock_page(page);
			return 0;
		}
		zero_user_segment(page, last_offset, PAGE_CACHE_SIZE);
	}
	bh = head;
	block = page->index << (PAGE_CACHE_SHIFT - s->s_blocksize_bits);
	last_block = (i_size_read(inode) - 1) >> inode->i_blkbits;
	/* first map all the buffers, logging any direct items we find */
	do {
		if (block > last_block) {
			/*
			 * This can happen when the block size is less than
			 * the page size.  The corresponding bytes in the page
			 * were zero filled above
			 */
			clear_buffer_dirty(bh);
			set_buffer_uptodate(bh);
		} else if ((checked || buffer_dirty(bh)) &&
		           (!buffer_mapped(bh) || (buffer_mapped(bh)
						       && bh->b_blocknr ==
						       0))) {
			/* not mapped yet, or it points to a direct item, search
			 * the btree for the mapping info, and log any direct
			 * items found
			 */
			if ((error = map_block_for_writepage(inode, bh, block))) {
				goto fail;
			}
		}
		bh = bh->b_this_page;
		block++;
	} while (bh != head);

	/*
	 * we start the transaction after map_block_for_writepage,
	 * because it can create holes in the file (an unbounded operation).
	 * starting it here, we can make a reliable estimate for how many
	 * blocks we're going to log
	 */
	if (checked) {
		ClearPageChecked(page);
		reiserfs_write_lock(s);
		error = journal_begin(&th, s, bh_per_page + 1);
		if (error) {
			reiserfs_write_unlock(s);
			goto fail;
		}
		reiserfs_update_inode_transaction(inode);
	}
	/* now go through and lock any dirty buffers on the page */
	do {
		get_bh(bh);
		if (!buffer_mapped(bh))
			continue;
		if (buffer_mapped(bh) && bh->b_blocknr == 0)
			continue;

		if (checked) {
			reiserfs_prepare_for_journal(s, bh, 1);
			journal_mark_dirty(&th, s, bh);
			continue;
		}
		/* from this point on, we know the buffer is mapped to a
		 * real block and not a direct item
		 */
		if (wbc->sync_mode != WB_SYNC_NONE || !wbc->nonblocking) {
			lock_buffer(bh);
		} else {
			if (!trylock_buffer(bh)) {
				redirty_page_for_writepage(wbc, page);
				continue;
			}
		}
		if (test_clear_buffer_dirty(bh)) {
			mark_buffer_async_write(bh);
		} else {
			unlock_buffer(bh);
		}
	} while ((bh = bh->b_this_page) != head);

	if (checked) {
		error = journal_end(&th, s, bh_per_page + 1);
		reiserfs_write_unlock(s);
		if (error)
			goto fail;
	}
	BUG_ON(PageWriteback(page));
	set_page_writeback(page);
	unlock_page(page);

	/*
	 * since any buffer might be the only dirty buffer on the page,
	 * the first submit_bh can bring the page out of writeback.
	 * be careful with the buffers.
	 */
	do {
		struct buffer_head *next = bh->b_this_page;
		if (buffer_async_write(bh)) {
			submit_bh(WRITE, bh);
			nr++;
		}
		put_bh(bh);
		bh = next;
	} while (bh != head);

	error = 0;
      done:
	if (nr == 0) {
		/*
		 * if this page only had a direct item, it is very possible for
		 * no io to be required without there being an error.  Or,
		 * someone else could have locked them and sent them down the
		 * pipe without locking the page
		 */
		bh = head;
		do {
			if (!buffer_uptodate(bh)) {
				partial = 1;
				break;
			}
			bh = bh->b_this_page;
		} while (bh != head);
		if (!partial)
			SetPageUptodate(page);
		end_page_writeback(page);
	}
	return error;

      fail:
	/* catches various errors, we need to make sure any valid dirty blocks
	 * get to the media.  The page is currently locked and not marked for
	 * writeback
	 */
	ClearPageUptodate(page);
	bh = head;
	do {
		get_bh(bh);
		if (buffer_mapped(bh) && buffer_dirty(bh) && bh->b_blocknr) {
			lock_buffer(bh);
			mark_buffer_async_write(bh);
		} else {
			/*
			 * clear any dirty bits that might have come from getting
			 * attached to a dirty page
			 */
			clear_buffer_dirty(bh);
		}
		bh = bh->b_this_page;
	} while (bh != head);
	SetPageError(page);
	BUG_ON(PageWriteback(page));
	set_page_writeback(page);
	unlock_page(page);
	do {
		struct buffer_head *next = bh->b_this_page;
		if (buffer_async_write(bh)) {
			clear_buffer_dirty(bh);
			submit_bh(WRITE, bh);
			nr++;
		}
		put_bh(bh);
		bh = next;
	} while (bh != head);
	goto done;
}