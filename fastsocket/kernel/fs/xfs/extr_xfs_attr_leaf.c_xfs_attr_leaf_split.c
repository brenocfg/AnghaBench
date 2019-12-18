#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xfs_dablk_t ;
struct TYPE_12__ {int /*<<< orphan*/  args; scalar_t__ inleaf; } ;
typedef  TYPE_1__ xfs_da_state_t ;
struct TYPE_13__ {scalar_t__ magic; int /*<<< orphan*/  bp; void* hashval; int /*<<< orphan*/  blkno; } ;
typedef  TYPE_2__ xfs_da_state_blk_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ XFS_ATTR_LEAF_MAGIC ; 
 int /*<<< orphan*/  trace_xfs_attr_leaf_add_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_xfs_attr_leaf_add_old (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_xfs_attr_leaf_split (int /*<<< orphan*/ ) ; 
 int xfs_attr_leaf_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int xfs_attr_leaf_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* xfs_attr_leaf_lasthash (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfs_attr_leaf_rebalance (TYPE_1__*,TYPE_2__*,TYPE_2__*) ; 
 int xfs_da_blk_link (TYPE_1__*,TYPE_2__*,TYPE_2__*) ; 
 int xfs_da_grow_inode (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int
xfs_attr_leaf_split(xfs_da_state_t *state, xfs_da_state_blk_t *oldblk,
				   xfs_da_state_blk_t *newblk)
{
	xfs_dablk_t blkno;
	int error;

	trace_xfs_attr_leaf_split(state->args);

	/*
	 * Allocate space for a new leaf node.
	 */
	ASSERT(oldblk->magic == XFS_ATTR_LEAF_MAGIC);
	error = xfs_da_grow_inode(state->args, &blkno);
	if (error)
		return(error);
	error = xfs_attr_leaf_create(state->args, blkno, &newblk->bp);
	if (error)
		return(error);
	newblk->blkno = blkno;
	newblk->magic = XFS_ATTR_LEAF_MAGIC;

	/*
	 * Rebalance the entries across the two leaves.
	 * NOTE: rebalance() currently depends on the 2nd block being empty.
	 */
	xfs_attr_leaf_rebalance(state, oldblk, newblk);
	error = xfs_da_blk_link(state, oldblk, newblk);
	if (error)
		return(error);

	/*
	 * Save info on "old" attribute for "atomic rename" ops, leaf_add()
	 * modifies the index/blkno/rmtblk/rmtblkcnt fields to show the
	 * "new" attrs info.  Will need the "old" info to remove it later.
	 *
	 * Insert the "new" entry in the correct block.
	 */
	if (state->inleaf) {
		trace_xfs_attr_leaf_add_old(state->args);
		error = xfs_attr_leaf_add(oldblk->bp, state->args);
	} else {
		trace_xfs_attr_leaf_add_new(state->args);
		error = xfs_attr_leaf_add(newblk->bp, state->args);
	}

	/*
	 * Update last hashval in each block since we added the name.
	 */
	oldblk->hashval = xfs_attr_leaf_lasthash(oldblk->bp, NULL);
	newblk->hashval = xfs_attr_leaf_lasthash(newblk->bp, NULL);
	return(error);
}