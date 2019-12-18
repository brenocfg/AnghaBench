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
typedef  scalar_t__ u64 ;
struct inode {scalar_t__ i_blkbits; } ;
struct extent_map {scalar_t__ block_start; scalar_t__ len; scalar_t__ start; int /*<<< orphan*/  flags; int /*<<< orphan*/  bdev; } ;
struct buffer_head {scalar_t__ b_size; int /*<<< orphan*/  b_bdev; scalar_t__ b_blocknr; } ;
struct btrfs_trans_handle {scalar_t__ block_start; scalar_t__ len; scalar_t__ start; int /*<<< orphan*/  flags; int /*<<< orphan*/  bdev; } ;
struct btrfs_root {scalar_t__ sectorsize; } ;
typedef  scalar_t__ sector_t ;
struct TYPE_2__ {int flags; int /*<<< orphan*/  io_tree; struct btrfs_root* root; } ;

/* Variables and functions */
 TYPE_1__* BTRFS_I (struct inode*) ; 
 int BTRFS_INODE_NODATACOW ; 
 int BTRFS_ORDERED_NOCOW ; 
 int BTRFS_ORDERED_PREALLOC ; 
 int ENOTBLK ; 
 int EXTENT_DELALLOC ; 
 int EXTENT_DIRTY ; 
 int /*<<< orphan*/  EXTENT_FLAG_COMPRESSED ; 
 int /*<<< orphan*/  EXTENT_FLAG_PREALLOC ; 
 int EXTENT_LOCKED ; 
 scalar_t__ EXTENT_MAP_HOLE ; 
 scalar_t__ EXTENT_MAP_INLINE ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 scalar_t__ IS_ERR (struct extent_map*) ; 
 int PTR_ERR (struct extent_map*) ; 
 int btrfs_add_ordered_extent_dio (struct inode*,scalar_t__,scalar_t__,scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  btrfs_end_transaction (struct extent_map*,struct btrfs_root*) ; 
 struct extent_map* btrfs_get_extent (struct inode*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 struct extent_map* btrfs_join_transaction (struct btrfs_root*) ; 
 struct extent_map* btrfs_new_extent_direct (struct inode*,struct extent_map*,scalar_t__,scalar_t__) ; 
 int can_nocow_odirect (struct extent_map*,struct inode*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  clear_extent_bit (int /*<<< orphan*/ *,scalar_t__,scalar_t__,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_extent_map (struct extent_map*) ; 
 scalar_t__ i_size_read (struct inode*) ; 
 int /*<<< orphan*/  i_size_write (struct inode*,scalar_t__) ; 
 scalar_t__ min (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  set_buffer_mapped (struct buffer_head*) ; 
 int /*<<< orphan*/  set_buffer_new (struct buffer_head*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unlock_extent (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int btrfs_get_blocks_direct(struct inode *inode, sector_t iblock,
				   struct buffer_head *bh_result, int create)
{
	struct extent_map *em;
	struct btrfs_root *root = BTRFS_I(inode)->root;
	u64 start = iblock << inode->i_blkbits;
	u64 len = bh_result->b_size;
	struct btrfs_trans_handle *trans;

	em = btrfs_get_extent(inode, NULL, 0, start, len, 0);
	if (IS_ERR(em))
		return PTR_ERR(em);

	/*
	 * Ok for INLINE and COMPRESSED extents we need to fallback on buffered
	 * io.  INLINE is special, and we could probably kludge it in here, but
	 * it's still buffered so for safety lets just fall back to the generic
	 * buffered path.
	 *
	 * For COMPRESSED we _have_ to read the entire extent in so we can
	 * decompress it, so there will be buffering required no matter what we
	 * do, so go ahead and fallback to buffered.
	 *
	 * We return -ENOTBLK because thats what makes DIO go ahead and go back
	 * to buffered IO.  Don't blame me, this is the price we pay for using
	 * the generic code.
	 */
	if (test_bit(EXTENT_FLAG_COMPRESSED, &em->flags) ||
	    em->block_start == EXTENT_MAP_INLINE) {
		free_extent_map(em);
		return -ENOTBLK;
	}

	/* Just a good old fashioned hole, return */
	if (!create && (em->block_start == EXTENT_MAP_HOLE ||
			test_bit(EXTENT_FLAG_PREALLOC, &em->flags))) {
		free_extent_map(em);
		/* DIO will do one hole at a time, so just unlock a sector */
		unlock_extent(&BTRFS_I(inode)->io_tree, start,
			      start + root->sectorsize - 1);
		return 0;
	}

	/*
	 * We don't allocate a new extent in the following cases
	 *
	 * 1) The inode is marked as NODATACOW.  In this case we'll just use the
	 * existing extent.
	 * 2) The extent is marked as PREALLOC.  We're good to go here and can
	 * just use the extent.
	 *
	 */
	if (!create) {
		len = em->len - (start - em->start);
		goto map;
	}

	if (test_bit(EXTENT_FLAG_PREALLOC, &em->flags) ||
	    ((BTRFS_I(inode)->flags & BTRFS_INODE_NODATACOW) &&
	     em->block_start != EXTENT_MAP_HOLE)) {
		int type;
		int ret;
		u64 block_start;

		if (test_bit(EXTENT_FLAG_PREALLOC, &em->flags))
			type = BTRFS_ORDERED_PREALLOC;
		else
			type = BTRFS_ORDERED_NOCOW;
		len = min(len, em->len - (start - em->start));
		block_start = em->block_start + (start - em->start);

		/*
		 * we're not going to log anything, but we do need
		 * to make sure the current transaction stays open
		 * while we look for nocow cross refs
		 */
		trans = btrfs_join_transaction(root);
		if (IS_ERR(trans))
			goto must_cow;

		if (can_nocow_odirect(trans, inode, start, len) == 1) {
			ret = btrfs_add_ordered_extent_dio(inode, start,
					   block_start, len, len, type);
			btrfs_end_transaction(trans, root);
			if (ret) {
				free_extent_map(em);
				return ret;
			}
			goto unlock;
		}
		btrfs_end_transaction(trans, root);
	}
must_cow:
	/*
	 * this will cow the extent, reset the len in case we changed
	 * it above
	 */
	len = bh_result->b_size;
	em = btrfs_new_extent_direct(inode, em, start, len);
	if (IS_ERR(em))
		return PTR_ERR(em);
	len = min(len, em->len - (start - em->start));
unlock:
	clear_extent_bit(&BTRFS_I(inode)->io_tree, start, start + len - 1,
			  EXTENT_LOCKED | EXTENT_DELALLOC | EXTENT_DIRTY, 1,
			  0, NULL, GFP_NOFS);
map:
	bh_result->b_blocknr = (em->block_start + (start - em->start)) >>
		inode->i_blkbits;
	bh_result->b_size = len;
	bh_result->b_bdev = em->bdev;
	set_buffer_mapped(bh_result);
	if (create) {
		if (!test_bit(EXTENT_FLAG_PREALLOC, &em->flags))
			set_buffer_new(bh_result);

		/*
		 * Need to update the i_size under the extent lock so buffered
		 * readers will get the updated i_size when we unlock.
		 */
		if (start + len > i_size_read(inode))
			i_size_write(inode, start + len);
	}

	free_extent_map(em);

	return 0;
}