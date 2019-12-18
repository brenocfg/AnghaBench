#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct xfs_mount {int /*<<< orphan*/  m_ddev_targp; int /*<<< orphan*/  m_rootip; } ;
typedef  scalar_t__ __uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRELE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYNC_WAIT ; 
 int /*<<< orphan*/  XFS_LOG_SYNC ; 
 int /*<<< orphan*/  XFS_bflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_errortag_clearall (struct xfs_mount*,int /*<<< orphan*/ ) ; 
 int xfs_flush_buftarg (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xfs_free_perag (struct xfs_mount*) ; 
 int /*<<< orphan*/  xfs_log_force (struct xfs_mount*,int /*<<< orphan*/ ) ; 
 int xfs_log_sbcount (struct xfs_mount*,int) ; 
 int /*<<< orphan*/  xfs_log_unmount (struct xfs_mount*) ; 
 int /*<<< orphan*/  xfs_log_unmount_write (struct xfs_mount*) ; 
 int /*<<< orphan*/  xfs_qm_unmount (struct xfs_mount*) ; 
 int /*<<< orphan*/  xfs_qm_unmount_quotas (struct xfs_mount*) ; 
 int /*<<< orphan*/  xfs_reclaim_inodes (struct xfs_mount*,int /*<<< orphan*/ ) ; 
 int xfs_reserve_blocks (struct xfs_mount*,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfs_rtunmount_inodes (struct xfs_mount*) ; 
 int /*<<< orphan*/  xfs_unmountfs_writesb (struct xfs_mount*) ; 
 int /*<<< orphan*/  xfs_uuid_unmount (struct xfs_mount*) ; 
 int /*<<< orphan*/  xfs_wait_buftarg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_warn (struct xfs_mount*,char*,...) ; 

void
xfs_unmountfs(
	struct xfs_mount	*mp)
{
	__uint64_t		resblks;
	int			error;

	xfs_qm_unmount_quotas(mp);
	xfs_rtunmount_inodes(mp);
	IRELE(mp->m_rootip);

	/*
	 * We can potentially deadlock here if we have an inode cluster
	 * that has been freed has its buffer still pinned in memory because
	 * the transaction is still sitting in a iclog. The stale inodes
	 * on that buffer will have their flush locks held until the
	 * transaction hits the disk and the callbacks run. the inode
	 * flush takes the flush lock unconditionally and with nothing to
	 * push out the iclog we will never get that unlocked. hence we
	 * need to force the log first.
	 */
	xfs_log_force(mp, XFS_LOG_SYNC);

	/*
	 * Do a delwri reclaim pass first so that as many dirty inodes are
	 * queued up for IO as possible. Then flush the buffers before making
	 * a synchronous path to catch all the remaining inodes are reclaimed.
	 * This makes the reclaim process as quick as possible by avoiding
	 * synchronous writeout and blocking on inodes already in the delwri
	 * state as much as possible.
	 */
	xfs_reclaim_inodes(mp, 0);
	XFS_bflush(mp->m_ddev_targp);
	xfs_reclaim_inodes(mp, SYNC_WAIT);

	xfs_qm_unmount(mp);

	/*
	 * Flush out the log synchronously so that we know for sure
	 * that nothing is pinned.  This is important because bflush()
	 * will skip pinned buffers.
	 */
	xfs_log_force(mp, XFS_LOG_SYNC);

	/*
	 * Unreserve any blocks we have so that when we unmount we don't account
	 * the reserved free space as used. This is really only necessary for
	 * lazy superblock counting because it trusts the incore superblock
	 * counters to be absolutely correct on clean unmount.
	 *
	 * We don't bother correcting this elsewhere for lazy superblock
	 * counting because on mount of an unclean filesystem we reconstruct the
	 * correct counter value and this is irrelevant.
	 *
	 * For non-lazy counter filesystems, this doesn't matter at all because
	 * we only every apply deltas to the superblock and hence the incore
	 * value does not matter....
	 */
	resblks = 0;
	error = xfs_reserve_blocks(mp, &resblks, NULL);
	if (error)
		xfs_warn(mp, "Unable to free reserved block pool. "
				"Freespace may not be correct on next mount.");

	error = xfs_log_sbcount(mp, 1);
	if (error)
		xfs_warn(mp, "Unable to update superblock counters. "
				"Freespace may not be correct on next mount.");
	xfs_unmountfs_writesb(mp);

	/*
	 * Make sure all buffers have been flushed and completed before
	 * unmounting the log.
	 */
	error = xfs_flush_buftarg(mp->m_ddev_targp, 1);
	if (error)
		xfs_warn(mp, "%d busy buffers during unmount.", error);
	xfs_wait_buftarg(mp->m_ddev_targp);

	xfs_log_unmount_write(mp);
	xfs_log_unmount(mp);
	xfs_uuid_unmount(mp);

#if defined(DEBUG)
	xfs_errortag_clearall(mp, 0);
#endif
	xfs_free_perag(mp);
}