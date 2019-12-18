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
struct xfs_mount {int dummy; } ;
struct xfs_buf {int dummy; } ;

/* Variables and functions */
 scalar_t__ XFS_FORCED_SHUTDOWN (struct xfs_mount*) ; 
 int /*<<< orphan*/  _RET_IP_ ; 
 int /*<<< orphan*/  trace_xfs_bdstrat_shut (struct xfs_buf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_bioerror_relse (struct xfs_buf*) ; 
 int /*<<< orphan*/  xfs_buf_iorequest (struct xfs_buf*) ; 

void
xfsbdstrat(
	struct xfs_mount	*mp,
	struct xfs_buf		*bp)
{
	if (XFS_FORCED_SHUTDOWN(mp)) {
		trace_xfs_bdstrat_shut(bp, _RET_IP_);
		xfs_bioerror_relse(bp);
		return;
	}

	xfs_buf_iorequest(bp);
}