#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_2__ ;
typedef  struct TYPE_27__   TYPE_1__ ;
typedef  struct TYPE_26__   TYPE_18__ ;

/* Type definitions */
struct TYPE_26__ {size_t active; TYPE_2__* blk; } ;
struct TYPE_27__ {TYPE_18__ path; int /*<<< orphan*/  args; TYPE_18__ altpath; } ;
typedef  TYPE_1__ xfs_da_state_t ;
struct TYPE_28__ {scalar_t__ magic; int /*<<< orphan*/ * bp; int /*<<< orphan*/  blkno; } ;
typedef  TYPE_2__ xfs_da_state_blk_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
#define  XFS_ATTR_LEAF_MAGIC 130 
#define  XFS_DA_NODE_MAGIC 129 
#define  XFS_DIR2_LEAFN_MAGIC 128 
 int /*<<< orphan*/  trace_xfs_da_join (int /*<<< orphan*/ ) ; 
 int xfs_attr_leaf_toosmall (TYPE_1__*,int*) ; 
 int /*<<< orphan*/  xfs_attr_leaf_unbalance (TYPE_1__*,TYPE_2__*,TYPE_2__*) ; 
 int xfs_da_blk_unlink (TYPE_1__*,TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  xfs_da_fixhashpath (TYPE_1__*,TYPE_18__*) ; 
 int /*<<< orphan*/  xfs_da_node_remove (TYPE_1__*,TYPE_2__*) ; 
 int xfs_da_node_toosmall (TYPE_1__*,int*) ; 
 int /*<<< orphan*/  xfs_da_node_unbalance (TYPE_1__*,TYPE_2__*,TYPE_2__*) ; 
 int xfs_da_root_join (TYPE_1__*,TYPE_2__*) ; 
 int xfs_da_shrink_inode (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfs_da_state_kill_altpath (TYPE_1__*) ; 
 int xfs_dir2_leafn_toosmall (TYPE_1__*,int*) ; 
 int /*<<< orphan*/  xfs_dir2_leafn_unbalance (TYPE_1__*,TYPE_2__*,TYPE_2__*) ; 

int
xfs_da_join(xfs_da_state_t *state)
{
	xfs_da_state_blk_t *drop_blk, *save_blk;
	int action, error;

	trace_xfs_da_join(state->args);

	action = 0;
	drop_blk = &state->path.blk[ state->path.active-1 ];
	save_blk = &state->altpath.blk[ state->path.active-1 ];
	ASSERT(state->path.blk[0].magic == XFS_DA_NODE_MAGIC);
	ASSERT(drop_blk->magic == XFS_ATTR_LEAF_MAGIC ||
	       drop_blk->magic == XFS_DIR2_LEAFN_MAGIC);

	/*
	 * Walk back up the tree joining/deallocating as necessary.
	 * When we stop dropping blocks, break out.
	 */
	for (  ; state->path.active >= 2; drop_blk--, save_blk--,
		 state->path.active--) {
		/*
		 * See if we can combine the block with a neighbor.
		 *   (action == 0) => no options, just leave
		 *   (action == 1) => coalesce, then unlink
		 *   (action == 2) => block empty, unlink it
		 */
		switch (drop_blk->magic) {
		case XFS_ATTR_LEAF_MAGIC:
			error = xfs_attr_leaf_toosmall(state, &action);
			if (error)
				return(error);
			if (action == 0)
				return(0);
			xfs_attr_leaf_unbalance(state, drop_blk, save_blk);
			break;
		case XFS_DIR2_LEAFN_MAGIC:
			error = xfs_dir2_leafn_toosmall(state, &action);
			if (error)
				return error;
			if (action == 0)
				return 0;
			xfs_dir2_leafn_unbalance(state, drop_blk, save_blk);
			break;
		case XFS_DA_NODE_MAGIC:
			/*
			 * Remove the offending node, fixup hashvals,
			 * check for a toosmall neighbor.
			 */
			xfs_da_node_remove(state, drop_blk);
			xfs_da_fixhashpath(state, &state->path);
			error = xfs_da_node_toosmall(state, &action);
			if (error)
				return(error);
			if (action == 0)
				return 0;
			xfs_da_node_unbalance(state, drop_blk, save_blk);
			break;
		}
		xfs_da_fixhashpath(state, &state->altpath);
		error = xfs_da_blk_unlink(state, drop_blk, save_blk);
		xfs_da_state_kill_altpath(state);
		if (error)
			return(error);
		error = xfs_da_shrink_inode(state->args, drop_blk->blkno,
							 drop_blk->bp);
		drop_blk->bp = NULL;
		if (error)
			return(error);
	}
	/*
	 * We joined all the way to the top.  If it turns out that
	 * we only have one entry in the root, make the child block
	 * the new root.
	 */
	xfs_da_node_remove(state, drop_blk);
	xfs_da_fixhashpath(state, &state->path);
	error = xfs_da_root_join(state, &state->path.blk[0]);
	return(error);
}