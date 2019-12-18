#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
struct TYPE_20__ {TYPE_4__* data; } ;
typedef  TYPE_1__ xfs_dabuf_t ;
struct TYPE_21__ {TYPE_5__* args; } ;
typedef  TYPE_2__ xfs_da_state_t ;
struct TYPE_22__ {scalar_t__ magic; scalar_t__ blkno; TYPE_1__* bp; } ;
typedef  TYPE_3__ xfs_da_state_blk_t ;
struct TYPE_23__ {scalar_t__ magic; void* forw; void* back; } ;
typedef  TYPE_4__ xfs_da_blkinfo_t ;
struct TYPE_24__ {int /*<<< orphan*/  trans; int /*<<< orphan*/  whichfork; int /*<<< orphan*/  dp; } ;
typedef  TYPE_5__ xfs_da_args_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
#define  XFS_ATTR_LEAF_MAGIC 130 
#define  XFS_DA_NODE_MAGIC 129 
#define  XFS_DIR2_LEAFN_MAGIC 128 
 scalar_t__ be16_to_cpu (scalar_t__) ; 
 scalar_t__ be32_to_cpu (void*) ; 
 void* cpu_to_be32 (scalar_t__) ; 
 int /*<<< orphan*/  trace_xfs_da_link_after (TYPE_5__*) ; 
 int /*<<< orphan*/  trace_xfs_da_link_before (TYPE_5__*) ; 
 int xfs_attr_leaf_order (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  xfs_da_buf_done (TYPE_1__*) ; 
 int /*<<< orphan*/  xfs_da_log_buf (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int xfs_da_node_order (TYPE_1__*,TYPE_1__*) ; 
 int xfs_da_read_buf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int,TYPE_1__**,int /*<<< orphan*/ ) ; 
 int xfs_dir2_leafn_order (TYPE_1__*,TYPE_1__*) ; 

int							/* error */
xfs_da_blk_link(xfs_da_state_t *state, xfs_da_state_blk_t *old_blk,
			       xfs_da_state_blk_t *new_blk)
{
	xfs_da_blkinfo_t *old_info, *new_info, *tmp_info;
	xfs_da_args_t *args;
	int before=0, error;
	xfs_dabuf_t *bp;

	/*
	 * Set up environment.
	 */
	args = state->args;
	ASSERT(args != NULL);
	old_info = old_blk->bp->data;
	new_info = new_blk->bp->data;
	ASSERT(old_blk->magic == XFS_DA_NODE_MAGIC ||
	       old_blk->magic == XFS_DIR2_LEAFN_MAGIC ||
	       old_blk->magic == XFS_ATTR_LEAF_MAGIC);
	ASSERT(old_blk->magic == be16_to_cpu(old_info->magic));
	ASSERT(new_blk->magic == be16_to_cpu(new_info->magic));
	ASSERT(old_blk->magic == new_blk->magic);

	switch (old_blk->magic) {
	case XFS_ATTR_LEAF_MAGIC:
		before = xfs_attr_leaf_order(old_blk->bp, new_blk->bp);
		break;
	case XFS_DIR2_LEAFN_MAGIC:
		before = xfs_dir2_leafn_order(old_blk->bp, new_blk->bp);
		break;
	case XFS_DA_NODE_MAGIC:
		before = xfs_da_node_order(old_blk->bp, new_blk->bp);
		break;
	}

	/*
	 * Link blocks in appropriate order.
	 */
	if (before) {
		/*
		 * Link new block in before existing block.
		 */
		trace_xfs_da_link_before(args);
		new_info->forw = cpu_to_be32(old_blk->blkno);
		new_info->back = old_info->back;
		if (old_info->back) {
			error = xfs_da_read_buf(args->trans, args->dp,
						be32_to_cpu(old_info->back),
						-1, &bp, args->whichfork);
			if (error)
				return(error);
			ASSERT(bp != NULL);
			tmp_info = bp->data;
			ASSERT(be16_to_cpu(tmp_info->magic) == be16_to_cpu(old_info->magic));
			ASSERT(be32_to_cpu(tmp_info->forw) == old_blk->blkno);
			tmp_info->forw = cpu_to_be32(new_blk->blkno);
			xfs_da_log_buf(args->trans, bp, 0, sizeof(*tmp_info)-1);
			xfs_da_buf_done(bp);
		}
		old_info->back = cpu_to_be32(new_blk->blkno);
	} else {
		/*
		 * Link new block in after existing block.
		 */
		trace_xfs_da_link_after(args);
		new_info->forw = old_info->forw;
		new_info->back = cpu_to_be32(old_blk->blkno);
		if (old_info->forw) {
			error = xfs_da_read_buf(args->trans, args->dp,
						be32_to_cpu(old_info->forw),
						-1, &bp, args->whichfork);
			if (error)
				return(error);
			ASSERT(bp != NULL);
			tmp_info = bp->data;
			ASSERT(tmp_info->magic == old_info->magic);
			ASSERT(be32_to_cpu(tmp_info->back) == old_blk->blkno);
			tmp_info->back = cpu_to_be32(new_blk->blkno);
			xfs_da_log_buf(args->trans, bp, 0, sizeof(*tmp_info)-1);
			xfs_da_buf_done(bp);
		}
		old_info->forw = cpu_to_be32(new_blk->blkno);
	}

	xfs_da_log_buf(args->trans, old_blk->bp, 0, sizeof(*tmp_info) - 1);
	xfs_da_log_buf(args->trans, new_blk->bp, 0, sizeof(*tmp_info) - 1);
	return(0);
}