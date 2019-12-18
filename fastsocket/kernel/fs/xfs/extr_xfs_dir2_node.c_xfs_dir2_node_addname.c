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
struct TYPE_19__ {TYPE_14__ path; int /*<<< orphan*/  extrablk; scalar_t__ extravalid; TYPE_2__* mp; int /*<<< orphan*/  node_ents; int /*<<< orphan*/  blocksize; TYPE_5__* args; } ;
typedef  TYPE_3__ xfs_da_state_t ;
struct TYPE_20__ {scalar_t__ magic; int /*<<< orphan*/  index; int /*<<< orphan*/  bp; } ;
typedef  TYPE_4__ xfs_da_state_blk_t ;
struct TYPE_21__ {int op_flags; scalar_t__ total; TYPE_1__* dp; } ;
typedef  TYPE_5__ xfs_da_args_t ;
struct TYPE_18__ {int /*<<< orphan*/  m_dir_node_ents; int /*<<< orphan*/  m_dirblksize; } ;
struct TYPE_17__ {TYPE_2__* i_mount; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int ENOENT ; 
 int ENOSPC ; 
 int XFS_DA_OP_JUSTCHECK ; 
 scalar_t__ XFS_DIR2_LEAFN_MAGIC ; 
 int /*<<< orphan*/  trace_xfs_dir2_node_addname (TYPE_5__*) ; 
 int /*<<< orphan*/  xfs_da_fixhashpath (TYPE_3__*,TYPE_14__*) ; 
 int xfs_da_node_lookup_int (TYPE_3__*,int*) ; 
 int xfs_da_split (TYPE_3__*) ; 
 TYPE_3__* xfs_da_state_alloc () ; 
 int /*<<< orphan*/  xfs_da_state_free (TYPE_3__*) ; 
 int xfs_dir2_leafn_add (int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ ) ; 
 int xfs_dir2_node_addname_int (TYPE_5__*,int /*<<< orphan*/ *) ; 

int						/* error */
xfs_dir2_node_addname(
	xfs_da_args_t		*args)		/* operation arguments */
{
	xfs_da_state_blk_t	*blk;		/* leaf block for insert */
	int			error;		/* error return value */
	int			rval;		/* sub-return value */
	xfs_da_state_t		*state;		/* btree cursor */

	trace_xfs_dir2_node_addname(args);

	/*
	 * Allocate and initialize the state (btree cursor).
	 */
	state = xfs_da_state_alloc();
	state->args = args;
	state->mp = args->dp->i_mount;
	state->blocksize = state->mp->m_dirblksize;
	state->node_ents = state->mp->m_dir_node_ents;
	/*
	 * Look up the name.  We're not supposed to find it, but
	 * this gives us the insertion point.
	 */
	error = xfs_da_node_lookup_int(state, &rval);
	if (error)
		rval = error;
	if (rval != ENOENT) {
		goto done;
	}
	/*
	 * Add the data entry to a data block.
	 * Extravalid is set to a freeblock found by lookup.
	 */
	rval = xfs_dir2_node_addname_int(args,
		state->extravalid ? &state->extrablk : NULL);
	if (rval) {
		goto done;
	}
	blk = &state->path.blk[state->path.active - 1];
	ASSERT(blk->magic == XFS_DIR2_LEAFN_MAGIC);
	/*
	 * Add the new leaf entry.
	 */
	rval = xfs_dir2_leafn_add(blk->bp, args, blk->index);
	if (rval == 0) {
		/*
		 * It worked, fix the hash values up the btree.
		 */
		if (!(args->op_flags & XFS_DA_OP_JUSTCHECK))
			xfs_da_fixhashpath(state, &state->path);
	} else {
		/*
		 * It didn't work, we need to split the leaf block.
		 */
		if (args->total == 0) {
			ASSERT(rval == ENOSPC);
			goto done;
		}
		/*
		 * Split the leaf block and insert the new entry.
		 */
		rval = xfs_da_split(state);
	}
done:
	xfs_da_state_free(state);
	return rval;
}