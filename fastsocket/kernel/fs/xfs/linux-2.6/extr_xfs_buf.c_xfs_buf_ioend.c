#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int b_flags; scalar_t__ b_error; int /*<<< orphan*/  b_iowait; int /*<<< orphan*/  b_iodone_work; scalar_t__ b_iodone; } ;
typedef  TYPE_1__ xfs_buf_t ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/  (*) (int /*<<< orphan*/ *)) ; 
 int XBF_ASYNC ; 
 int XBF_DONE ; 
 int XBF_READ ; 
 int XBF_READ_AHEAD ; 
 int XBF_WRITE ; 
 int /*<<< orphan*/  _RET_IP_ ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_xfs_buf_iodone (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_buf_iodone_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfslogd_workqueue ; 

void
xfs_buf_ioend(
	xfs_buf_t		*bp,
	int			schedule)
{
	trace_xfs_buf_iodone(bp, _RET_IP_);

	bp->b_flags &= ~(XBF_READ | XBF_WRITE | XBF_READ_AHEAD);
	if (bp->b_error == 0)
		bp->b_flags |= XBF_DONE;

	if ((bp->b_iodone) || (bp->b_flags & XBF_ASYNC)) {
		if (schedule) {
			INIT_WORK(&bp->b_iodone_work, xfs_buf_iodone_work);
			queue_work(xfslogd_workqueue, &bp->b_iodone_work);
		} else {
			xfs_buf_iodone_work(&bp->b_iodone_work);
		}
	} else {
		complete(&bp->b_iowait);
	}
}