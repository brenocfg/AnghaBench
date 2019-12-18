#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int b_flags; int /*<<< orphan*/  b_sema; int /*<<< orphan*/  b_hold; } ;
typedef  TYPE_1__ xfs_buf_t ;

/* Variables and functions */
 int XBF_ASYNC ; 
 int XBF_DELWRI ; 
 int /*<<< orphan*/  XB_CLEAR_OWNER (TYPE_1__*) ; 
 int /*<<< orphan*/  _RET_IP_ ; 
 int _XBF_DELWRI_Q ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_xfs_buf_unlock (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfs_buf_delwri_queue (TYPE_1__*,int /*<<< orphan*/ ) ; 

void
xfs_buf_unlock(
	xfs_buf_t		*bp)
{
	if ((bp->b_flags & (XBF_DELWRI|_XBF_DELWRI_Q)) == XBF_DELWRI) {
		atomic_inc(&bp->b_hold);
		bp->b_flags |= XBF_ASYNC;
		xfs_buf_delwri_queue(bp, 0);
	}

	XB_CLEAR_OWNER(bp);
	up(&bp->b_sema);

	trace_xfs_buf_unlock(bp, _RET_IP_);
}