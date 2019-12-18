#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xfs_trans_t ;
struct TYPE_8__ {scalar_t__ sb_sectsize; } ;
struct TYPE_7__ {TYPE_2__ m_sb; } ;
typedef  TYPE_1__ xfs_mount_t ;
typedef  scalar_t__ uint ;

/* Variables and functions */
 int /*<<< orphan*/  KM_SLEEP ; 
 int /*<<< orphan*/  XFS_DEFAULT_LOG_COUNT ; 
 int XFS_SB_FDBLOCKS ; 
 int XFS_SB_ICOUNT ; 
 int XFS_SB_IFREE ; 
 int /*<<< orphan*/  XFS_TRANS_SB_COUNT ; 
 int /*<<< orphan*/ * _xfs_trans_alloc (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_fs_writable (TYPE_1__*) ; 
 int /*<<< orphan*/  xfs_icsb_sync_counters (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_mod_sb (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  xfs_sb_version_haslazysbcount (TYPE_2__*) ; 
 int /*<<< orphan*/  xfs_trans_cancel (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int xfs_trans_commit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int xfs_trans_reserve (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_trans_set_sync (int /*<<< orphan*/ *) ; 

int
xfs_log_sbcount(
	xfs_mount_t	*mp,
	uint		sync)
{
	xfs_trans_t	*tp;
	int		error;

	if (!xfs_fs_writable(mp))
		return 0;

	xfs_icsb_sync_counters(mp, 0);

	/*
	 * we don't need to do this if we are updating the superblock
	 * counters on every modification.
	 */
	if (!xfs_sb_version_haslazysbcount(&mp->m_sb))
		return 0;

	tp = _xfs_trans_alloc(mp, XFS_TRANS_SB_COUNT, KM_SLEEP);
	error = xfs_trans_reserve(tp, 0, mp->m_sb.sb_sectsize + 128, 0, 0,
					XFS_DEFAULT_LOG_COUNT);
	if (error) {
		xfs_trans_cancel(tp, 0);
		return error;
	}

	xfs_mod_sb(tp, XFS_SB_IFREE | XFS_SB_ICOUNT | XFS_SB_FDBLOCKS);
	if (sync)
		xfs_trans_set_sync(tp);
	error = xfs_trans_commit(tp, 0);
	return error;
}