#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct xfs_buf {int /*<<< orphan*/  b_iodone; TYPE_1__* b_target; } ;
struct TYPE_2__ {int /*<<< orphan*/  bt_mount; } ;

/* Variables and functions */
 int /*<<< orphan*/  XFS_BUF_ISREAD (struct xfs_buf*) ; 
 scalar_t__ XFS_FORCED_SHUTDOWN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _RET_IP_ ; 
 int /*<<< orphan*/  trace_xfs_bdstrat_shut (struct xfs_buf*,int /*<<< orphan*/ ) ; 
 int xfs_bioerror (struct xfs_buf*) ; 
 int xfs_bioerror_relse (struct xfs_buf*) ; 
 int /*<<< orphan*/  xfs_buf_iorequest (struct xfs_buf*) ; 

int
xfs_bdstrat_cb(
	struct xfs_buf	*bp)
{
	if (XFS_FORCED_SHUTDOWN(bp->b_target->bt_mount)) {
		trace_xfs_bdstrat_shut(bp, _RET_IP_);
		/*
		 * Metadata write that didn't get logged but
		 * written delayed anyway. These aren't associated
		 * with a transaction, and can be ignored.
		 */
		if (!bp->b_iodone && !XFS_BUF_ISREAD(bp))
			return xfs_bioerror_relse(bp);
		else
			return xfs_bioerror(bp);
	}

	xfs_buf_iorequest(bp);
	return 0;
}