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
struct xfs_ail {int /*<<< orphan*/  xa_task; int /*<<< orphan*/  xa_target; } ;

/* Variables and functions */
 scalar_t__ XFS_LSN_CMP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up_process (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_trans_ail_copy_lsn (struct xfs_ail*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
xfsaild_wakeup(
	struct xfs_ail		*ailp,
	xfs_lsn_t		threshold_lsn)
{
	/* only ever move the target forwards */
	if (XFS_LSN_CMP(threshold_lsn, ailp->xa_target) > 0) {
		xfs_trans_ail_copy_lsn(ailp, &ailp->xa_target, &threshold_lsn);
		wake_up_process(ailp->xa_task);
	}
}