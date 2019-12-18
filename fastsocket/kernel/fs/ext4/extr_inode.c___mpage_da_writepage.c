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
struct page {scalar_t__ index; } ;
struct mpage_da_data {scalar_t__ next_page; scalar_t__ first_page; scalar_t__ b_size; int b_state; scalar_t__ io_done; scalar_t__ b_blocknr; struct inode* inode; } ;
struct inode {int i_blkbits; } ;
struct buffer_head {int b_state; int /*<<< orphan*/  b_size; struct buffer_head* b_this_page; } ;
typedef  int sector_t ;

/* Variables and functions */
 int BH_Dirty ; 
 int BH_FLAGS ; 
 int BH_Uptodate ; 
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int MPAGE_DA_EXTENT_TAIL ; 
 int PAGE_CACHE_SHIFT ; 
 int /*<<< orphan*/  PAGE_CACHE_SIZE ; 
 scalar_t__ buffer_dirty (struct buffer_head*) ; 
 int /*<<< orphan*/  buffer_locked (struct buffer_head*) ; 
 scalar_t__ buffer_mapped (struct buffer_head*) ; 
 scalar_t__ ext4_bh_delay_or_unwritten (int /*<<< orphan*/ *,struct buffer_head*) ; 
 int /*<<< orphan*/  mpage_add_bh_to_extent (struct mpage_da_data*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mpage_da_map_and_submit (struct mpage_da_data*) ; 
 struct buffer_head* page_buffers (struct page*) ; 
 int /*<<< orphan*/  page_has_buffers (struct page*) ; 
 int /*<<< orphan*/  redirty_page_for_writepage (struct writeback_control*,struct page*) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

__attribute__((used)) static int __mpage_da_writepage(struct page *page,
				struct writeback_control *wbc, void *data)
{
	struct mpage_da_data *mpd = data;
	struct inode *inode = mpd->inode;
	struct buffer_head *bh, *head;
	sector_t logical;

	/*
	 * Can we merge this page to current extent?
	 */
	if (mpd->next_page != page->index) {
		/*
		 * Nope, we can't. So, we map non-allocated blocks
		 * and start IO on them
		 */
		if (mpd->next_page != mpd->first_page) {
			mpage_da_map_and_submit(mpd);
			/*
			 * skip rest of the page in the page_vec
			 */
			redirty_page_for_writepage(wbc, page);
			unlock_page(page);
			return MPAGE_DA_EXTENT_TAIL;
		}

		/*
		 * Start next extent of pages ...
		 */
		mpd->first_page = page->index;

		/*
		 * ... and blocks
		 */
		mpd->b_size = 0;
		mpd->b_state = 0;
		mpd->b_blocknr = 0;
	}

	mpd->next_page = page->index + 1;
	logical = (sector_t) page->index <<
		  (PAGE_CACHE_SHIFT - inode->i_blkbits);

	if (!page_has_buffers(page)) {
		mpage_add_bh_to_extent(mpd, logical, PAGE_CACHE_SIZE,
				       (1 << BH_Dirty) | (1 << BH_Uptodate));
		if (mpd->io_done)
			return MPAGE_DA_EXTENT_TAIL;
	} else {
		/*
		 * Page with regular buffer heads, just add all dirty ones
		 */
		head = page_buffers(page);
		bh = head;
		do {
			BUG_ON(buffer_locked(bh));
			/*
			 * We need to try to allocate
			 * unmapped blocks in the same page.
			 * Otherwise we won't make progress
			 * with the page in ext4_writepage
			 */
			if (ext4_bh_delay_or_unwritten(NULL, bh)) {
				mpage_add_bh_to_extent(mpd, logical,
						       bh->b_size,
						       bh->b_state);
				if (mpd->io_done)
					return MPAGE_DA_EXTENT_TAIL;
			} else if (buffer_dirty(bh) && (buffer_mapped(bh))) {
				/*
				 * mapped dirty buffer. We need to update
				 * the b_state because we look at
				 * b_state in mpage_da_map_blocks. We don't
				 * update b_size because if we find an
				 * unmapped buffer_head later we need to
				 * use the b_state flag of that buffer_head.
				 */
				if (mpd->b_size == 0)
					mpd->b_state = bh->b_state & BH_FLAGS;
			}
			logical++;
		} while ((bh = bh->b_this_page) != head);
	}

	return 0;
}