#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xfs_trans_t ;
struct TYPE_5__ {scalar_t__ sb_sectsize; } ;
struct TYPE_6__ {TYPE_1__ m_sb; } ;
typedef  TYPE_2__ xfs_mount_t ;

/* Variables and functions */
 int /*<<< orphan*/  KM_SLEEP ; 
 int /*<<< orphan*/  XFS_DEFAULT_LOG_COUNT ; 
 int /*<<< orphan*/  XFS_SB_UUID ; 
 int /*<<< orphan*/  XFS_TRANS_DUMMY1 ; 
 int /*<<< orphan*/ * _xfs_trans_alloc (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_mod_sb (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_trans_cancel (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int xfs_trans_commit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int xfs_trans_reserve (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_trans_set_sync (int /*<<< orphan*/ *) ; 

int
xfs_fs_log_dummy(
	xfs_mount_t	*mp)
{
	xfs_trans_t	*tp;
	int		error;

	tp = _xfs_trans_alloc(mp, XFS_TRANS_DUMMY1, KM_SLEEP);
	error = xfs_trans_reserve(tp, 0, mp->m_sb.sb_sectsize + 128, 0, 0,
					XFS_DEFAULT_LOG_COUNT);
	if (error) {
		xfs_trans_cancel(tp, 0);
		return error;
	}

	/* log the UUID because it is an unchanging field */
	xfs_mod_sb(tp, XFS_SB_UUID);
	xfs_trans_set_sync(tp);
	return xfs_trans_commit(tp, 0);
}