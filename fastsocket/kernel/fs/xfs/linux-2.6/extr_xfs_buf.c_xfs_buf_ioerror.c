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
struct TYPE_4__ {unsigned short b_error; } ;
typedef  TYPE_1__ xfs_buf_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  _RET_IP_ ; 
 int /*<<< orphan*/  trace_xfs_buf_ioerror (TYPE_1__*,int,int /*<<< orphan*/ ) ; 

void
xfs_buf_ioerror(
	xfs_buf_t		*bp,
	int			error)
{
	ASSERT(error >= 0 && error <= 0xffff);
	bp->b_error = (unsigned short)error;
	trace_xfs_buf_ioerror(bp, error, _RET_IP_);
}