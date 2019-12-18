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
typedef  int /*<<< orphan*/  xfs_lsn_t ;
typedef  int /*<<< orphan*/  xfs_log_item_t ;
struct xfs_ail {int /*<<< orphan*/  xa_target; int /*<<< orphan*/  xa_mount; } ;

/* Variables and functions */
 int /*<<< orphan*/  XFS_FORCED_SHUTDOWN (int /*<<< orphan*/ ) ; 
 scalar_t__ XFS_LSN_CMP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * xfs_ail_min (struct xfs_ail*) ; 
 int /*<<< orphan*/  xfsaild_wakeup (struct xfs_ail*,int /*<<< orphan*/ ) ; 

void
xfs_ail_push(
	struct xfs_ail	*ailp,
	xfs_lsn_t	threshold_lsn)
{
	xfs_log_item_t	*lip;

	lip = xfs_ail_min(ailp);
	if (lip && !XFS_FORCED_SHUTDOWN(ailp->xa_mount)) {
		if (XFS_LSN_CMP(threshold_lsn, ailp->xa_target) > 0)
			xfsaild_wakeup(ailp, threshold_lsn);
	}
}