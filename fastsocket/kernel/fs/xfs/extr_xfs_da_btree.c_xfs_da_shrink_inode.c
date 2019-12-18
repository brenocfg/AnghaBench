#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xfs_trans_t ;
struct TYPE_8__ {int m_dirblkfsbs; } ;
typedef  TYPE_1__ xfs_mount_t ;
struct TYPE_9__ {TYPE_1__* i_mount; } ;
typedef  TYPE_2__ xfs_inode_t ;
typedef  int /*<<< orphan*/  xfs_dabuf_t ;
typedef  int /*<<< orphan*/  xfs_dablk_t ;
struct TYPE_10__ {int whichfork; int /*<<< orphan*/  flist; int /*<<< orphan*/  firstblock; int /*<<< orphan*/ * trans; TYPE_2__* dp; } ;
typedef  TYPE_3__ xfs_da_args_t ;

/* Variables and functions */
 int ENOSPC ; 
 int XFS_BMAPI_METADATA ; 
 int XFS_DATA_FORK ; 
 int /*<<< orphan*/  trace_xfs_da_shrink_inode (TYPE_3__*) ; 
 int xfs_bmapi_aflag (int) ; 
 int xfs_bunmapi (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  xfs_da_binval (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int xfs_da_swap_lastblock (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 

int
xfs_da_shrink_inode(xfs_da_args_t *args, xfs_dablk_t dead_blkno,
		    xfs_dabuf_t *dead_buf)
{
	xfs_inode_t *dp;
	int done, error, w, count;
	xfs_trans_t *tp;
	xfs_mount_t *mp;

	trace_xfs_da_shrink_inode(args);

	dp = args->dp;
	w = args->whichfork;
	tp = args->trans;
	mp = dp->i_mount;
	if (w == XFS_DATA_FORK)
		count = mp->m_dirblkfsbs;
	else
		count = 1;
	for (;;) {
		/*
		 * Remove extents.  If we get ENOSPC for a dir we have to move
		 * the last block to the place we want to kill.
		 */
		if ((error = xfs_bunmapi(tp, dp, dead_blkno, count,
				xfs_bmapi_aflag(w)|XFS_BMAPI_METADATA,
				0, args->firstblock, args->flist,
				&done)) == ENOSPC) {
			if (w != XFS_DATA_FORK)
				break;
			if ((error = xfs_da_swap_lastblock(args, &dead_blkno,
					&dead_buf)))
				break;
		} else {
			break;
		}
	}
	xfs_da_binval(tp, dead_buf);
	return error;
}