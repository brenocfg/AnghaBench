#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct inode {int /*<<< orphan*/  i_sb; int /*<<< orphan*/  i_mode; } ;
struct ext3_inode_info {int /*<<< orphan*/  truncate_mutex; int /*<<< orphan*/  i_block_alloc_info; } ;
struct buffer_head {int dummy; } ;
typedef  int /*<<< orphan*/  sector_t ;
typedef  int /*<<< orphan*/  handle_t ;
typedef  scalar_t__ ext3_fsblk_t ;
struct TYPE_10__ {int /*<<< orphan*/  key; struct buffer_head* bh; int /*<<< orphan*/ * p; } ;
typedef  TYPE_1__ Indirect ;

/* Variables and functions */
 int /*<<< orphan*/  BUFFER_TRACE (struct buffer_head*,char*) ; 
 int EAGAIN ; 
 int EIO ; 
 struct ext3_inode_info* EXT3_I (struct inode*) ; 
 int /*<<< orphan*/  J_ASSERT (int) ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  clear_buffer_new (struct buffer_head*) ; 
 int ext3_alloc_branch (int /*<<< orphan*/ *,struct inode*,int,int*,scalar_t__,int*,TYPE_1__*) ; 
 int ext3_blks_to_allocate (TYPE_1__*,int,unsigned long,int) ; 
 int ext3_block_to_path (struct inode*,int /*<<< orphan*/ ,int*,int*) ; 
 scalar_t__ ext3_find_goal (struct inode*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 TYPE_1__* ext3_get_branch (struct inode*,int,int*,TYPE_1__*,int*) ; 
 int /*<<< orphan*/  ext3_init_block_alloc_info (struct inode*) ; 
 int ext3_splice_branch (int /*<<< orphan*/ *,struct inode*,int /*<<< orphan*/ ,TYPE_1__*,int,int) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  map_bh (struct buffer_head*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_buffer_boundary (struct buffer_head*) ; 
 int /*<<< orphan*/  set_buffer_new (struct buffer_head*) ; 
 int /*<<< orphan*/  trace_ext3_get_blocks_enter (struct inode*,int /*<<< orphan*/ ,unsigned long,int) ; 
 int /*<<< orphan*/  trace_ext3_get_blocks_exit (struct inode*,int /*<<< orphan*/ ,scalar_t__,int,int) ; 
 int /*<<< orphan*/  verify_chain (TYPE_1__*,TYPE_1__*) ; 

int ext3_get_blocks_handle(handle_t *handle, struct inode *inode,
		sector_t iblock, unsigned long maxblocks,
		struct buffer_head *bh_result,
		int create)
{
	int err = -EIO;
	int offsets[4];
	Indirect chain[4];
	Indirect *partial;
	ext3_fsblk_t goal;
	int indirect_blks;
	int blocks_to_boundary = 0;
	int depth;
	struct ext3_inode_info *ei = EXT3_I(inode);
	int count = 0;
	ext3_fsblk_t first_block = 0;


	trace_ext3_get_blocks_enter(inode, iblock, maxblocks, create);
	J_ASSERT(handle != NULL || create == 0);
	depth = ext3_block_to_path(inode,iblock,offsets,&blocks_to_boundary);

	if (depth == 0)
		goto out;

	partial = ext3_get_branch(inode, depth, offsets, chain, &err);

	/* Simplest case - block found, no allocation needed */
	if (!partial) {
		first_block = le32_to_cpu(chain[depth - 1].key);
		clear_buffer_new(bh_result);
		count++;
		/*map more blocks*/
		while (count < maxblocks && count <= blocks_to_boundary) {
			ext3_fsblk_t blk;

			if (!verify_chain(chain, chain + depth - 1)) {
				/*
				 * Indirect block might be removed by
				 * truncate while we were reading it.
				 * Handling of that case: forget what we've
				 * got now. Flag the err as EAGAIN, so it
				 * will reread.
				 */
				err = -EAGAIN;
				count = 0;
				break;
			}
			blk = le32_to_cpu(*(chain[depth-1].p + count));

			if (blk == first_block + count)
				count++;
			else
				break;
		}
		if (err != -EAGAIN)
			goto got_it;
	}

	/* Next simple case - plain lookup or failed read of indirect block */
	if (!create || err == -EIO)
		goto cleanup;

	mutex_lock(&ei->truncate_mutex);

	/*
	 * If the indirect block is missing while we are reading
	 * the chain(ext3_get_branch() returns -EAGAIN err), or
	 * if the chain has been changed after we grab the semaphore,
	 * (either because another process truncated this branch, or
	 * another get_block allocated this branch) re-grab the chain to see if
	 * the request block has been allocated or not.
	 *
	 * Since we already block the truncate/other get_block
	 * at this point, we will have the current copy of the chain when we
	 * splice the branch into the tree.
	 */
	if (err == -EAGAIN || !verify_chain(chain, partial)) {
		while (partial > chain) {
			brelse(partial->bh);
			partial--;
		}
		partial = ext3_get_branch(inode, depth, offsets, chain, &err);
		if (!partial) {
			count++;
			mutex_unlock(&ei->truncate_mutex);
			if (err)
				goto cleanup;
			clear_buffer_new(bh_result);
			goto got_it;
		}
	}

	/*
	 * Okay, we need to do block allocation.  Lazily initialize the block
	 * allocation info here if necessary
	*/
	if (S_ISREG(inode->i_mode) && (!ei->i_block_alloc_info))
		ext3_init_block_alloc_info(inode);

	goal = ext3_find_goal(inode, iblock, partial);

	/* the number of blocks need to allocate for [d,t]indirect blocks */
	indirect_blks = (chain + depth) - partial - 1;

	/*
	 * Next look up the indirect map to count the totoal number of
	 * direct blocks to allocate for this branch.
	 */
	count = ext3_blks_to_allocate(partial, indirect_blks,
					maxblocks, blocks_to_boundary);
	/*
	 * Block out ext3_truncate while we alter the tree
	 */
	err = ext3_alloc_branch(handle, inode, indirect_blks, &count, goal,
				offsets + (partial - chain), partial);

	/*
	 * The ext3_splice_branch call will free and forget any buffers
	 * on the new chain if there is a failure, but that risks using
	 * up transaction credits, especially for bitmaps where the
	 * credits cannot be returned.  Can we handle this somehow?  We
	 * may need to return -EAGAIN upwards in the worst case.  --sct
	 */
	if (!err)
		err = ext3_splice_branch(handle, inode, iblock,
					partial, indirect_blks, count);
	mutex_unlock(&ei->truncate_mutex);
	if (err)
		goto cleanup;

	set_buffer_new(bh_result);
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
	trace_ext3_get_blocks_exit(inode, iblock,
				   depth ? le32_to_cpu(chain[depth-1].key) : 0,
				   count, err);
	return err;
}