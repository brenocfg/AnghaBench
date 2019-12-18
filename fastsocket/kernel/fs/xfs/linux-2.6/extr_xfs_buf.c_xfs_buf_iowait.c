#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int b_error; int /*<<< orphan*/  b_iowait; TYPE_1__* b_target; int /*<<< orphan*/  b_io_remaining; } ;
typedef  TYPE_2__ xfs_buf_t ;
struct TYPE_6__ {int /*<<< orphan*/  bt_bdi; } ;

/* Variables and functions */
 int /*<<< orphan*/  _RET_IP_ ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  blk_run_backing_dev (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_xfs_buf_iowait (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_xfs_buf_iowait_done (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

int
xfs_buf_iowait(
	xfs_buf_t		*bp)
{
	trace_xfs_buf_iowait(bp, _RET_IP_);

	if (atomic_read(&bp->b_io_remaining))
		blk_run_backing_dev(bp->b_target->bt_bdi, NULL);
	if (!bp->b_error)
		wait_for_completion(&bp->b_iowait);

	trace_xfs_buf_iowait_done(bp, _RET_IP_);
	return bp->b_error;
}