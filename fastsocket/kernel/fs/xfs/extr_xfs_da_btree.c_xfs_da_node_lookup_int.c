#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_9__ ;
typedef  struct TYPE_27__   TYPE_8__ ;
typedef  struct TYPE_26__   TYPE_6__ ;
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;
typedef  struct TYPE_20__   TYPE_15__ ;

/* Type definitions */
typedef  scalar_t__ xfs_dahash_t ;
typedef  scalar_t__ xfs_dablk_t ;
struct TYPE_20__ {int active; TYPE_4__* blk; } ;
struct TYPE_23__ {TYPE_15__ path; TYPE_1__* mp; TYPE_8__* args; } ;
typedef  TYPE_3__ xfs_da_state_t ;
struct TYPE_24__ {scalar_t__ magic; scalar_t__ hashval; int index; scalar_t__ blkno; TYPE_9__* bp; } ;
typedef  TYPE_4__ xfs_da_state_blk_t ;
struct TYPE_25__ {int /*<<< orphan*/  before; int /*<<< orphan*/  hashval; } ;
typedef  TYPE_5__ xfs_da_node_entry_t ;
struct TYPE_22__ {int /*<<< orphan*/  count; } ;
struct TYPE_26__ {TYPE_5__* btree; TYPE_2__ hdr; int /*<<< orphan*/  magic; } ;
typedef  TYPE_6__ xfs_da_intnode_t ;
typedef  TYPE_6__ xfs_da_blkinfo_t ;
struct TYPE_27__ {scalar_t__ whichfork; scalar_t__ hashval; int index; scalar_t__ blkno; int /*<<< orphan*/  dp; int /*<<< orphan*/  trans; } ;
typedef  TYPE_8__ xfs_da_args_t ;
struct TYPE_28__ {TYPE_6__* data; } ;
struct TYPE_21__ {scalar_t__ m_dirleafblk; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int EFSCORRUPTED ; 
 int ENOATTR ; 
 int ENOENT ; 
 scalar_t__ XFS_ATTR_LEAF_MAGIC ; 
 scalar_t__ XFS_DATA_FORK ; 
 scalar_t__ XFS_DA_NODE_MAGIC ; 
 int XFS_DA_NODE_MAXDEPTH ; 
 scalar_t__ XFS_DIR2_LEAFN_MAGIC ; 
 int XFS_ERROR (int) ; 
 void* be16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ be32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ xfs_attr_leaf_lasthash (TYPE_9__*,int /*<<< orphan*/ *) ; 
 int xfs_attr_leaf_lookup_int (TYPE_9__*,TYPE_8__*) ; 
 int xfs_da_path_shift (TYPE_3__*,TYPE_15__*,int,int,int*) ; 
 int xfs_da_read_buf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int,TYPE_9__**,scalar_t__) ; 
 scalar_t__ xfs_dir2_leafn_lasthash (TYPE_9__*,int /*<<< orphan*/ *) ; 
 int xfs_dir2_leafn_lookup_int (TYPE_9__*,TYPE_8__*,int*,TYPE_3__*) ; 

int							/* error */
xfs_da_node_lookup_int(xfs_da_state_t *state, int *result)
{
	xfs_da_state_blk_t *blk;
	xfs_da_blkinfo_t *curr;
	xfs_da_intnode_t *node;
	xfs_da_node_entry_t *btree;
	xfs_dablk_t blkno;
	int probe, span, max, error, retval;
	xfs_dahash_t hashval, btreehashval;
	xfs_da_args_t *args;

	args = state->args;

	/*
	 * Descend thru the B-tree searching each level for the right
	 * node to use, until the right hashval is found.
	 */
	blkno = (args->whichfork == XFS_DATA_FORK)? state->mp->m_dirleafblk : 0;
	for (blk = &state->path.blk[0], state->path.active = 1;
			 state->path.active <= XFS_DA_NODE_MAXDEPTH;
			 blk++, state->path.active++) {
		/*
		 * Read the next node down in the tree.
		 */
		blk->blkno = blkno;
		error = xfs_da_read_buf(args->trans, args->dp, blkno,
					-1, &blk->bp, args->whichfork);
		if (error) {
			blk->blkno = 0;
			state->path.active--;
			return(error);
		}
		curr = blk->bp->data;
		blk->magic = be16_to_cpu(curr->magic);
		ASSERT(blk->magic == XFS_DA_NODE_MAGIC ||
		       blk->magic == XFS_DIR2_LEAFN_MAGIC ||
		       blk->magic == XFS_ATTR_LEAF_MAGIC);

		/*
		 * Search an intermediate node for a match.
		 */
		if (blk->magic == XFS_DA_NODE_MAGIC) {
			node = blk->bp->data;
			max = be16_to_cpu(node->hdr.count);
			blk->hashval = be32_to_cpu(node->btree[max-1].hashval);

			/*
			 * Binary search.  (note: small blocks will skip loop)
			 */
			probe = span = max / 2;
			hashval = args->hashval;
			for (btree = &node->btree[probe]; span > 4;
				   btree = &node->btree[probe]) {
				span /= 2;
				btreehashval = be32_to_cpu(btree->hashval);
				if (btreehashval < hashval)
					probe += span;
				else if (btreehashval > hashval)
					probe -= span;
				else
					break;
			}
			ASSERT((probe >= 0) && (probe < max));
			ASSERT((span <= 4) || (be32_to_cpu(btree->hashval) == hashval));

			/*
			 * Since we may have duplicate hashval's, find the first
			 * matching hashval in the node.
			 */
			while ((probe > 0) && (be32_to_cpu(btree->hashval) >= hashval)) {
				btree--;
				probe--;
			}
			while ((probe < max) && (be32_to_cpu(btree->hashval) < hashval)) {
				btree++;
				probe++;
			}

			/*
			 * Pick the right block to descend on.
			 */
			if (probe == max) {
				blk->index = max-1;
				blkno = be32_to_cpu(node->btree[max-1].before);
			} else {
				blk->index = probe;
				blkno = be32_to_cpu(btree->before);
			}
		} else if (blk->magic == XFS_ATTR_LEAF_MAGIC) {
			blk->hashval = xfs_attr_leaf_lasthash(blk->bp, NULL);
			break;
		} else if (blk->magic == XFS_DIR2_LEAFN_MAGIC) {
			blk->hashval = xfs_dir2_leafn_lasthash(blk->bp, NULL);
			break;
		}
	}

	/*
	 * A leaf block that ends in the hashval that we are interested in
	 * (final hashval == search hashval) means that the next block may
	 * contain more entries with the same hashval, shift upward to the
	 * next leaf and keep searching.
	 */
	for (;;) {
		if (blk->magic == XFS_DIR2_LEAFN_MAGIC) {
			retval = xfs_dir2_leafn_lookup_int(blk->bp, args,
							&blk->index, state);
		} else if (blk->magic == XFS_ATTR_LEAF_MAGIC) {
			retval = xfs_attr_leaf_lookup_int(blk->bp, args);
			blk->index = args->index;
			args->blkno = blk->blkno;
		} else {
			ASSERT(0);
			return XFS_ERROR(EFSCORRUPTED);
		}
		if (((retval == ENOENT) || (retval == ENOATTR)) &&
		    (blk->hashval == args->hashval)) {
			error = xfs_da_path_shift(state, &state->path, 1, 1,
							 &retval);
			if (error)
				return(error);
			if (retval == 0) {
				continue;
			} else if (blk->magic == XFS_ATTR_LEAF_MAGIC) {
				/* path_shift() gives ENOENT */
				retval = XFS_ERROR(ENOATTR);
			}
		}
		break;
	}
	*result = retval;
	return(0);
}