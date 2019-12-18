#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  b_sema; } ;
typedef  TYPE_1__ xfs_buf_t ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  XB_SET_OWNER (TYPE_1__*) ; 
 int /*<<< orphan*/  _RET_IP_ ; 
 scalar_t__ down_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_xfs_buf_cond_lock (TYPE_1__*,int /*<<< orphan*/ ) ; 

int
xfs_buf_cond_lock(
	xfs_buf_t		*bp)
{
	int			locked;

	locked = down_trylock(&bp->b_sema) == 0;
	if (locked)
		XB_SET_OWNER(bp);

	trace_xfs_buf_cond_lock(bp, _RET_IP_);
	return locked ? 0 : -EBUSY;
}