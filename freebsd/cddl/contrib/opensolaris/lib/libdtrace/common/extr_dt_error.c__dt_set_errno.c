#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int dt_errno; char const* dt_errfile; int dt_errline; } ;
typedef  TYPE_1__ dtrace_hdl_t ;

/* Variables and functions */

int
_dt_set_errno(dtrace_hdl_t *dtp, int err, const char *errfile, int errline)
{
	dtp->dt_errno = err;
	dtp->dt_errfile = errfile;
	dtp->dt_errline = errline;
	return (-1);
}