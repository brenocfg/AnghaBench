#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct inode {int /*<<< orphan*/  i_sb; } ;
struct buffer_head {int dummy; } ;
typedef  int /*<<< orphan*/  handle_t ;
typedef  int /*<<< orphan*/  ext4_lblk_t ;
typedef  scalar_t__ ext4_fsblk_t ;
struct TYPE_8__ {struct buffer_head* bh; int /*<<< orphan*/  key; int /*<<< orphan*/ * p; } ;
typedef  TYPE_1__ Indirect ;

/* Variables and functions */
 int /*<<< orphan*/  BUFFER_TRACE (struct buffer_head*,char*) ; 
 int EIO ; 
 int EXT4_GET_BLOCKS_CREATE ; 
 int /*<<< orphan*/  EXT4_INODE_EXTENTS ; 
 int /*<<< orphan*/  J_ASSERT (int) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  clear_buffer_new (struct buffer_head*) ; 
 int ext4_alloc_branch (int /*<<< orphan*/ *,struct inode*,int /*<<< orphan*/ ,int,int*,scalar_t__,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int ext4_blks_to_allocate (TYPE_1__*,int,unsigned int,int) ; 
 int ext4_block_to_path (struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 scalar_t__ ext4_find_goal (struct inode*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 TYPE_1__* ext4_get_branch (struct inode*,int,int /*<<< orphan*/ *,TYPE_1__*,int*) ; 
 int ext4_splice_branch (int /*<<< orphan*/ *,struct inode*,int /*<<< orphan*/ ,TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  ext4_test_inode_flag (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_update_inode_fsync_trans (int /*<<< orphan*/ *,struct inode*,int) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  map_bh (struct buffer_head*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  set_buffer_boundary (struct buffer_head*) ; 
 int /*<<< orphan*/  set_buffer_new (struct buffer_head*) ; 

__attribute__((used)) static int ext4_ind_get_blocks(handle_t *handle, struct inode *inode,
			       ext4_lblk_t iblock, unsigned int maxblocks,
			       struct buffer_head *bh_result,
			       int flags)
{
	int err = -EIO;
	ext4_lblk_t offsets[4];
	Indirect chain[4];
	Indirect *partial;
	ext4_fsblk_t goal;
	int indirect_blks;
	int blocks_to_boundary = 0;
	int depth;
	int count = 0;
	ext4_fsblk_t first_block = 0;

	J_ASSERT(!(ext4_test_inode_flag(inode, EXT4_INODE_EXTENTS)));
	J_ASSERT(handle != NULL || (flags & EXT4_GET_BLOCKS_CREATE) == 0);
	depth = ext4_block_to_path(inode, iblock, offsets,
				   &blocks_to_boundary);

	if (depth == 0)
		goto out;

	partial = ext4_get_branch(inode, depth, offsets, chain, &err);

	/* Simplest case - block found, no allocation needed */
	if (!partial) {
		first_block = le32_to_cpu(chain[depth - 1].key);
		clear_buffer_new(bh_result);
		count++;
		/*map more blocks*/
		while (count < maxblocks && count <= blocks_to_boundary) {
			ext4_fsblk_t blk;

			blk = le32_to_cpu(*(chain[depth-1].p + count));

			if (blk == first_block + count)
				count++;
			else
				break;
		}
		goto got_it;
	}

	/* Next simple case - plain lookup or failed read of indirect block */
	if ((flags & EXT4_GET_BLOCKS_CREATE) == 0 || err == -EIO)
		goto cleanup;

	/*
	 * Okay, we need to do block allocation.
	*/
	goal = ext4_find_goal(inode, iblock, partial);

	/* the number of blocks need to allocate for [d,t]indirect blocks */
	indirect_blks = (chain + depth) - partial - 1;

	/*
	 * Next look up the indirect map to count the totoal number of
	 * direct blocks to allocate for this branch.
	 */
	count = ext4_blks_to_allocate(partial, indirect_blks,
					maxblocks, blocks_to_boundary);
	/*
	 * Block out ext4_truncate while we alter the tree
	 */
	err = ext4_alloc_branch(handle, inode, iblock, indirect_blks,
				&count, goal,
				offsets + (partial - chain), partial);

	/*
	 * The ext4_splice_branch call will free and forget any buffers
	 * on the new chain if there is a failure, but that risks using
	 * up transaction credits, especially for bitmaps where the
	 * credits cannot be returned.  Can we handle this somehow?  We
	 * may need to return -EAGAIN upwards in the worst case.  --sct
	 */
	if (!err)
		err = ext4_splice_branch(handle, inode, iblock,
					 partial, indirect_blks, count);
	if (err)
		goto cleanup;

	set_buffer_new(bh_result);

	ext4_update_inode_fsync_trans(handle, inode, 1);
got_it:
	map_bh(bh_result, inode->i_sb, le32_to_cpu(chain[depth-1].key));
	if (count > blocks_to_boundary)
		set_buffer_boundary(bh_result);
	err = count;
	/* Clean up and exit */
	partial = chain + depth - 1;	/* the whole chain */
cleanup:
	while (partial > chain) {
		BUFFER_TRACE(partial->bh, "call brelse");
		brelse(partial->bh);
		partial--;
	}
	BUFFER_TRACE(bh_result, "returned");
out:
	return err;
}