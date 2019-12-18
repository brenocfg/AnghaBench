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
typedef  int __int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  XFS_DEFAULT_LOG_COUNT ; 
 int XFS_SB_BAD_FEATURES2 ; 
 int XFS_SB_FEATURES2 ; 
 int XFS_SB_UNIT ; 
 int XFS_SB_UUID ; 
 int XFS_SB_VERSIONNUM ; 
 int XFS_SB_WIDTH ; 
 int /*<<< orphan*/  XFS_TRANS_SB_UNIT ; 
 int /*<<< orphan*/  xfs_mod_sb (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * xfs_trans_alloc (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_trans_cancel (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int xfs_trans_commit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int xfs_trans_reserve (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
xfs_mount_log_sb(
	xfs_mount_t	*mp,
	__int64_t	fields)
{
	xfs_trans_t	*tp;
	int		error;

	ASSERT(fields & (XFS_SB_UNIT | XFS_SB_WIDTH | XFS_SB_UUID |
			 XFS_SB_FEATURES2 | XFS_SB_BAD_FEATURES2 |
			 XFS_SB_VERSIONNUM));

	tp = xfs_trans_alloc(mp, XFS_TRANS_SB_UNIT);
	error = xfs_trans_reserve(tp, 0, mp->m_sb.sb_sectsize + 128, 0, 0,
				XFS_DEFAULT_LOG_COUNT);
	if (error) {
		xfs_trans_cancel(tp, 0);
		return error;
	}
	xfs_mod_sb(tp, fields);
	error = xfs_trans_commit(tp, 0);
	return error;
}