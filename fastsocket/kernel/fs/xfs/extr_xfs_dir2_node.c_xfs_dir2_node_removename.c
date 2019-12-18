#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_14__ ;

/* Type definitions */
struct TYPE_16__ {int active; TYPE_4__* blk; } ;
struct TYPE_19__ {int extravalid; TYPE_14__ path; int /*<<< orphan*/  extrablk; TYPE_2__* mp; int /*<<< orphan*/  node_ents; int /*<<< orphan*/  blocksize; TYPE_5__* args; } ;
typedef  TYPE_3__ xfs_da_state_t ;
struct TYPE_20__ {scalar_t__ magic; int /*<<< orphan*/  index; int /*<<< orphan*/  bp; } ;
typedef  TYPE_4__ xfs_da_state_blk_t ;
struct TYPE_21__ {TYPE_1__* dp; } ;
typedef  TYPE_5__ xfs_da_args_t ;
struct TYPE_18__ {int /*<<< orphan*/  m_dir_node_ents; int /*<<< orphan*/  m_dirblksize; } ;
struct TYPE_17__ {TYPE_2__* i_mount; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int EEXIST ; 
 scalar_t__ XFS_DIR2_LEAFN_MAGIC ; 
 int /*<<< orphan*/  trace_xfs_dir2_node_removename (TYPE_5__*) ; 
 int /*<<< orphan*/  xfs_da_fixhashpath (TYPE_3__*,TYPE_14__*) ; 
 int xfs_da_join (TYPE_3__*) ; 
 int xfs_da_node_lookup_int (TYPE_3__*,int*) ; 
 TYPE_3__* xfs_da_state_alloc () ; 
 int /*<<< orphan*/  xfs_da_state_free (TYPE_3__*) ; 
 int xfs_dir2_leafn_remove (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 int xfs_dir2_node_to_leaf (TYPE_3__*) ; 

int						/* error */
xfs_dir2_node_removename(
	xfs_da_args_t		*args)		/* operation arguments */
{
	xfs_da_state_blk_t	*blk;		/* leaf block */
	int			error;		/* error return value */
	int			rval;		/* operation return value */
	xfs_da_state_t		*state;		/* btree cursor */

	trace_xfs_dir2_node_removename(args);

	/*
	 * Allocate and initialize the btree cursor.
	 */
	state = xfs_da_state_alloc();
	state->args = args;
	state->mp = args->dp->i_mount;
	state->blocksize = state->mp->m_dirblksize;
	state->node_ents = state->mp->m_dir_node_ents;
	/*
	 * Look up the entry we're deleting, set up the cursor.
	 */
	error = xfs_da_node_lookup_int(state, &rval);
	if (error)
		rval = error;
	/*
	 * Didn't find it, upper layer screwed up.
	 */
	if (rval != EEXIST) {
		xfs_da_state_free(state);
		return rval;
	}
	blk = &state->path.blk[state->path.active - 1];
	ASSERT(blk->magic == XFS_DIR2_LEAFN_MAGIC);
	ASSERT(state->extravalid);
	/*
	 * Remove the leaf and data entries.
	 * Extrablk refers to the data block.
	 */
	error = xfs_dir2_leafn_remove(args, blk->bp, blk->index,
		&state->extrablk, &rval);
	if (error)
		return error;
	/*
	 * Fix the hash values up the btree.
	 */
	xfs_da_fixhashpath(state, &state->path);
	/*
	 * If we need to join leaf blocks, do it.
	 */
	if (rval && state->path.active > 1)
		error = xfs_da_join(state);
	/*
	 * If no errors so far, try conversion to leaf format.
	 */
	if (!error)
		error = xfs_dir2_node_to_leaf(state);
	xfs_da_state_free(state);
	return error;
}