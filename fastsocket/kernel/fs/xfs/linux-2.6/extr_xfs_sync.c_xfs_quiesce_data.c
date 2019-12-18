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
struct xfs_mount {scalar_t__ m_rtdev_targp; int /*<<< orphan*/  m_ddev_targp; } ;

/* Variables and functions */
 int /*<<< orphan*/  SYNC_TRYLOCK ; 
 int /*<<< orphan*/  SYNC_WAIT ; 
 int /*<<< orphan*/  XFS_bflush (scalar_t__) ; 
 int /*<<< orphan*/  xfs_flush_buftarg (int /*<<< orphan*/ ,int) ; 
 int xfs_fs_log_dummy (struct xfs_mount*) ; 
 int /*<<< orphan*/  xfs_qm_sync (struct xfs_mount*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_sync_data (struct xfs_mount*,int /*<<< orphan*/ ) ; 
 int xfs_sync_fsdata (struct xfs_mount*) ; 

int
xfs_quiesce_data(
	struct xfs_mount	*mp)
{
	int			error, error2 = 0;

	/* push non-blocking */
	xfs_sync_data(mp, 0);
	xfs_qm_sync(mp, SYNC_TRYLOCK);

	/* push and block till complete */
	xfs_sync_data(mp, SYNC_WAIT);

	xfs_qm_sync(mp, SYNC_WAIT);

	/* write superblock and hoover up shutdown errors */
	error = xfs_sync_fsdata(mp);

	/* make sure all delwri buffers are written out */
	xfs_flush_buftarg(mp->m_ddev_targp, 1);

	/* Ensure the log tail is up to date by loggin a dummy record. */
	error2 = xfs_fs_log_dummy(mp);

	/* flush data-only devices */
	if (mp->m_rtdev_targp)
		XFS_bflush(mp->m_rtdev_targp);

	return error ? error : error2;
}