#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int b_flags; int /*<<< orphan*/  b_io_remaining; } ;
typedef  TYPE_1__ xfs_buf_t ;

/* Variables and functions */
 int XBF_DELWRI ; 
 int XBF_WRITE ; 
 int /*<<< orphan*/  _RET_IP_ ; 
 int /*<<< orphan*/  _xfs_buf_ioapply (TYPE_1__*) ; 
 int /*<<< orphan*/  _xfs_buf_ioend (TYPE_1__*,int) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  trace_xfs_buf_iorequest (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_buf_delwri_queue (TYPE_1__*,int) ; 
 int /*<<< orphan*/  xfs_buf_hold (TYPE_1__*) ; 
 int /*<<< orphan*/  xfs_buf_rele (TYPE_1__*) ; 
 int /*<<< orphan*/  xfs_buf_wait_unpin (TYPE_1__*) ; 

void
xfs_buf_iorequest(
	xfs_buf_t		*bp)
{
	trace_xfs_buf_iorequest(bp, _RET_IP_);

	if (bp->b_flags & XBF_DELWRI) {
		xfs_buf_delwri_queue(bp, 1);
		return;
	}

	if (bp->b_flags & XBF_WRITE) {
		xfs_buf_wait_unpin(bp);
	}

	xfs_buf_hold(bp);

	/* Set the count to 1 initially, this will stop an I/O
	 * completion callout which happens before we have started
	 * all the I/O from calling xfs_buf_ioend too early.
	 */
	atomic_set(&bp->b_io_remaining, 1);
	_xfs_buf_ioapply(bp);
	_xfs_buf_ioend(bp, 1);

	xfs_buf_rele(bp);
}