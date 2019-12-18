#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xfs_off_t ;
typedef  int /*<<< orphan*/  xfs_buftarg_t ;
struct TYPE_9__ {int b_flags; } ;
typedef  TYPE_1__ xfs_buf_t ;
typedef  int xfs_buf_flags_t ;

/* Variables and functions */
 int XBF_ASYNC ; 
 int XBF_LOCK ; 
 int XBF_READ ; 
 int XBF_TRYLOCK ; 
 int /*<<< orphan*/  XFS_BUF_ISDONE (TYPE_1__*) ; 
 int /*<<< orphan*/  XFS_STATS_INC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _RET_IP_ ; 
 int /*<<< orphan*/  _xfs_buf_read (TYPE_1__*,int) ; 
 int /*<<< orphan*/  trace_xfs_buf_read (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xb_get_read ; 
 TYPE_1__* xfs_buf_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t,int) ; 
 int /*<<< orphan*/  xfs_buf_rele (TYPE_1__*) ; 
 int /*<<< orphan*/  xfs_buf_unlock (TYPE_1__*) ; 

xfs_buf_t *
xfs_buf_read(
	xfs_buftarg_t		*target,
	xfs_off_t		ioff,
	size_t			isize,
	xfs_buf_flags_t		flags)
{
	xfs_buf_t		*bp;

	flags |= XBF_READ;

	bp = xfs_buf_get(target, ioff, isize, flags);
	if (bp) {
		trace_xfs_buf_read(bp, flags, _RET_IP_);

		if (!XFS_BUF_ISDONE(bp)) {
			XFS_STATS_INC(xb_get_read);
			_xfs_buf_read(bp, flags);
		} else if (flags & XBF_ASYNC) {
			/*
			 * Read ahead call which is already satisfied,
			 * drop the buffer
			 */
			goto no_buffer;
		} else {
			/* We do not want read in the flags */
			bp->b_flags &= ~XBF_READ;
		}
	}

	return bp;

 no_buffer:
	if (flags & (XBF_LOCK | XBF_TRYLOCK))
		xfs_buf_unlock(bp);
	xfs_buf_rele(bp);
	return NULL;
}