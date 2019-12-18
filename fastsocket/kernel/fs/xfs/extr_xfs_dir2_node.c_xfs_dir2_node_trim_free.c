#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xfs_trans_t ;
typedef  int /*<<< orphan*/  xfs_mount_t ;
struct TYPE_13__ {int /*<<< orphan*/ * i_mount; } ;
typedef  TYPE_2__ xfs_inode_t ;
typedef  scalar_t__ xfs_fileoff_t ;
struct TYPE_12__ {int /*<<< orphan*/  nused; int /*<<< orphan*/  magic; } ;
struct TYPE_14__ {TYPE_1__ hdr; } ;
typedef  TYPE_3__ xfs_dir2_free_t ;
struct TYPE_15__ {TYPE_3__* data; } ;
typedef  TYPE_4__ xfs_dabuf_t ;
typedef  int /*<<< orphan*/  xfs_dablk_t ;
struct TYPE_16__ {int /*<<< orphan*/ * trans; TYPE_2__* dp; } ;
typedef  TYPE_5__ xfs_da_args_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int ENOSPC ; 
 int /*<<< orphan*/  XFS_DATA_FORK ; 
 scalar_t__ XFS_DIR2_FREE_MAGIC ; 
 scalar_t__ be32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  xfs_da_brelse (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int xfs_da_read_buf (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ,int,TYPE_4__**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_dir2_da_to_db (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int xfs_dir2_shrink_inode (TYPE_5__*,int /*<<< orphan*/ ,TYPE_4__*) ; 

int						/* error */
xfs_dir2_node_trim_free(
	xfs_da_args_t		*args,		/* operation arguments */
	xfs_fileoff_t		fo,		/* free block number */
	int			*rvalp)		/* out: did something */
{
	xfs_dabuf_t		*bp;		/* freespace buffer */
	xfs_inode_t		*dp;		/* incore directory inode */
	int			error;		/* error return code */
	xfs_dir2_free_t		*free;		/* freespace structure */
	xfs_mount_t		*mp;		/* filesystem mount point */
	xfs_trans_t		*tp;		/* transaction pointer */

	dp = args->dp;
	mp = dp->i_mount;
	tp = args->trans;
	/*
	 * Read the freespace block.
	 */
	if (unlikely(error = xfs_da_read_buf(tp, dp, (xfs_dablk_t)fo, -2, &bp,
			XFS_DATA_FORK))) {
		return error;
	}

	/*
	 * There can be holes in freespace.  If fo is a hole, there's
	 * nothing to do.
	 */
	if (bp == NULL) {
		return 0;
	}
	free = bp->data;
	ASSERT(be32_to_cpu(free->hdr.magic) == XFS_DIR2_FREE_MAGIC);
	/*
	 * If there are used entries, there's nothing to do.
	 */
	if (be32_to_cpu(free->hdr.nused) > 0) {
		xfs_da_brelse(tp, bp);
		*rvalp = 0;
		return 0;
	}
	/*
	 * Blow the block away.
	 */
	if ((error =
	    xfs_dir2_shrink_inode(args, xfs_dir2_da_to_db(mp, (xfs_dablk_t)fo),
		    bp))) {
		/*
		 * Can't fail with ENOSPC since that only happens with no
		 * space reservation, when breaking up an extent into two
		 * pieces.  This is the last block of an extent.
		 */
		ASSERT(error != ENOSPC);
		xfs_da_brelse(tp, bp);
		return error;
	}
	/*
	 * Return that we succeeded.
	 */
	*rvalp = 1;
	return 0;
}