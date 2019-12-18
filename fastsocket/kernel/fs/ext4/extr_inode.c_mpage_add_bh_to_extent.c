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
struct mpage_da_data {int b_size; scalar_t__ b_blocknr; unsigned long b_state; TYPE_2__* inode; } ;
typedef  scalar_t__ sector_t ;
struct TYPE_4__ {int i_blkbits; TYPE_1__* i_sb; } ;
struct TYPE_3__ {int s_blocksize; } ;

/* Variables and functions */
 unsigned long BH_FLAGS ; 
 int /*<<< orphan*/  EXT4_INODE_EXTENTS ; 
 int EXT4_MAX_TRANS_DATA ; 
 int /*<<< orphan*/  ext4_test_inode_flag (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpage_da_map_and_submit (struct mpage_da_data*) ; 

__attribute__((used)) static void mpage_add_bh_to_extent(struct mpage_da_data *mpd,
				   sector_t logical, size_t b_size,
				   unsigned long b_state)
{
	sector_t next;
	int nrblocks = mpd->b_size >> mpd->inode->i_blkbits;

	/*
	 * XXX Don't go larger than mballoc is willing to allocate
	 * This is a stopgap solution.  We eventually need to fold
	 * mpage_da_submit_io() into this function and then call
	 * ext4_get_blocks() multiple times in a loop
	 */
	if (nrblocks >= 8*1024*1024/mpd->inode->i_sb->s_blocksize)
		goto flush_it;

	/* check if thereserved journal credits might overflow */
	if (!(ext4_test_inode_flag(mpd->inode, EXT4_INODE_EXTENTS))) {
		if (nrblocks >= EXT4_MAX_TRANS_DATA) {
			/*
			 * With non-extent format we are limited by the journal
			 * credit available.  Total credit needed to insert
			 * nrblocks contiguous blocks is dependent on the
			 * nrblocks.  So limit nrblocks.
			 */
			goto flush_it;
		} else if ((nrblocks + (b_size >> mpd->inode->i_blkbits)) >
				EXT4_MAX_TRANS_DATA) {
			/*
			 * Adding the new buffer_head would make it cross the
			 * allowed limit for which we have journal credit
			 * reserved. So limit the new bh->b_size
			 */
			b_size = (EXT4_MAX_TRANS_DATA - nrblocks) <<
						mpd->inode->i_blkbits;
			/* we will do mpage_da_submit_io in the next loop */
		}
	}
	/*
	 * First block in the extent
	 */
	if (mpd->b_size == 0) {
		mpd->b_blocknr = logical;
		mpd->b_size = b_size;
		mpd->b_state = b_state & BH_FLAGS;
		return;
	}

	next = mpd->b_blocknr + nrblocks;
	/*
	 * Can we merge the block to our big extent?
	 */
	if (logical == next && (b_state & BH_FLAGS) == mpd->b_state) {
		mpd->b_size += b_size;
		return;
	}

flush_it:
	/*
	 * We couldn't merge the block to our extent, so we
	 * need to flush current  extent and start new one
	 */
	mpage_da_map_and_submit(mpd);
	return;
}