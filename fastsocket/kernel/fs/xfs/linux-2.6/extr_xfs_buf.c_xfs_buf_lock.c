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
struct TYPE_8__ {int b_flags; int /*<<< orphan*/  b_sema; TYPE_1__* b_target; int /*<<< orphan*/  b_io_remaining; int /*<<< orphan*/  b_pin_count; } ;
typedef  TYPE_2__ xfs_buf_t ;
struct TYPE_7__ {int /*<<< orphan*/  bt_bdi; int /*<<< orphan*/  bt_mount; } ;

/* Variables and functions */
 int XBF_STALE ; 
 int /*<<< orphan*/  XB_SET_OWNER (TYPE_2__*) ; 
 int /*<<< orphan*/  _RET_IP_ ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  blk_run_backing_dev (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  down (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_xfs_buf_lock (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_xfs_buf_lock_done (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_log_force (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
xfs_buf_lock(
	xfs_buf_t		*bp)
{
	trace_xfs_buf_lock(bp, _RET_IP_);

	if (atomic_read(&bp->b_pin_count) && (bp->b_flags & XBF_STALE))
		xfs_log_force(bp->b_target->bt_mount, 0);
	if (atomic_read(&bp->b_io_remaining))
		blk_run_backing_dev(bp->b_target->bt_bdi, NULL);
	down(&bp->b_sema);
	XB_SET_OWNER(bp);

	trace_xfs_buf_lock_done(bp, _RET_IP_);
}