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
typedef  int /*<<< orphan*/  xfs_trans_t ;
typedef  int /*<<< orphan*/  xfs_mount_t ;
struct TYPE_12__ {scalar_t__ di_aformat; } ;
struct TYPE_13__ {TYPE_1__ i_d; int /*<<< orphan*/ * i_mount; } ;
typedef  TYPE_2__ xfs_inode_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  XFS_ATTRINVAL_LOG_COUNT ; 
 int /*<<< orphan*/  XFS_ATTRINVAL_LOG_RES (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XFS_ATTR_FORK ; 
 scalar_t__ XFS_DINODE_FMT_LOCAL ; 
 int /*<<< orphan*/  XFS_ILOCK_EXCL ; 
 int /*<<< orphan*/  XFS_ILOCK_SHARED ; 
 int /*<<< orphan*/  XFS_ILOG_CORE ; 
 int /*<<< orphan*/  XFS_NOT_DQATTACHED (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int XFS_TRANS_ABORT ; 
 int /*<<< orphan*/  XFS_TRANS_ATTRINVAL ; 
 int /*<<< orphan*/  XFS_TRANS_PERM_LOG_RES ; 
 int XFS_TRANS_RELEASE_LOG_RES ; 
 int xfs_attr_root_inactive (int /*<<< orphan*/ **,TYPE_2__*) ; 
 int /*<<< orphan*/  xfs_ilock (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_inode_hasattr (TYPE_2__*) ; 
 int xfs_itruncate_finish (int /*<<< orphan*/ **,TYPE_2__*,long long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_iunlock (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * xfs_trans_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_trans_cancel (int /*<<< orphan*/ *,int) ; 
 int xfs_trans_commit (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  xfs_trans_ijoin (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  xfs_trans_log_inode (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int xfs_trans_reserve (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int								/* error */
xfs_attr_inactive(xfs_inode_t *dp)
{
	xfs_trans_t *trans;
	xfs_mount_t *mp;
	int error;

	mp = dp->i_mount;
	ASSERT(! XFS_NOT_DQATTACHED(mp, dp));

	xfs_ilock(dp, XFS_ILOCK_SHARED);
	if (!xfs_inode_hasattr(dp) ||
	    dp->i_d.di_aformat == XFS_DINODE_FMT_LOCAL) {
		xfs_iunlock(dp, XFS_ILOCK_SHARED);
		return 0;
	}
	xfs_iunlock(dp, XFS_ILOCK_SHARED);

	/*
	 * Start our first transaction of the day.
	 *
	 * All future transactions during this code must be "chained" off
	 * this one via the trans_dup() call.  All transactions will contain
	 * the inode, and the inode will always be marked with trans_ihold().
	 * Since the inode will be locked in all transactions, we must log
	 * the inode in every transaction to let it float upward through
	 * the log.
	 */
	trans = xfs_trans_alloc(mp, XFS_TRANS_ATTRINVAL);
	if ((error = xfs_trans_reserve(trans, 0, XFS_ATTRINVAL_LOG_RES(mp), 0,
				      XFS_TRANS_PERM_LOG_RES,
				      XFS_ATTRINVAL_LOG_COUNT))) {
		xfs_trans_cancel(trans, 0);
		return(error);
	}
	xfs_ilock(dp, XFS_ILOCK_EXCL);

	/*
	 * No need to make quota reservations here. We expect to release some
	 * blocks, not allocate, in the common case.
	 */
	xfs_trans_ijoin(trans, dp);

	/*
	 * Decide on what work routines to call based on the inode size.
	 */
	if (!xfs_inode_hasattr(dp) ||
	    dp->i_d.di_aformat == XFS_DINODE_FMT_LOCAL) {
		error = 0;
		goto out;
	}
	error = xfs_attr_root_inactive(&trans, dp);
	if (error)
		goto out;

	error = xfs_itruncate_finish(&trans, dp, 0LL, XFS_ATTR_FORK);
	if (error)
		goto out;

	/*
	 * Commit the last in the sequence of transactions.
	 */
	xfs_trans_log_inode(trans, dp, XFS_ILOG_CORE);
	error = xfs_trans_commit(trans, XFS_TRANS_RELEASE_LOG_RES);
	xfs_iunlock(dp, XFS_ILOCK_EXCL);

	return(error);

out:
	xfs_trans_cancel(trans, XFS_TRANS_RELEASE_LOG_RES|XFS_TRANS_ABORT);
	xfs_iunlock(dp, XFS_ILOCK_EXCL);
	return(error);
}