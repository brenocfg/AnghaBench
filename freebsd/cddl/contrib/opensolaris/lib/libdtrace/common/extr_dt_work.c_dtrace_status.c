#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ hrtime_t ;
typedef  scalar_t__ dtrace_optval_t ;
struct TYPE_10__ {int dt_statusgen; scalar_t__* dt_options; scalar_t__ dt_laststatus; scalar_t__ dt_stopped; TYPE_6__* dt_status; int /*<<< orphan*/  dt_active; } ;
typedef  TYPE_1__ dtrace_hdl_t ;
struct TYPE_11__ {scalar_t__ dtst_filled; scalar_t__ dtst_exiting; } ;

/* Variables and functions */
 int /*<<< orphan*/  DTRACEIOC_STATUS ; 
 size_t DTRACEOPT_BUFPOLICY ; 
 scalar_t__ DTRACEOPT_BUFPOLICY_FILL ; 
 size_t DTRACEOPT_STATUSRATE ; 
 int DTRACE_STATUS_EXITED ; 
 int DTRACE_STATUS_FILLED ; 
 int DTRACE_STATUS_NONE ; 
 int DTRACE_STATUS_OKAY ; 
 int DTRACE_STATUS_STOPPED ; 
 int dt_handle_status (TYPE_1__*,TYPE_6__*,TYPE_6__*) ; 
 int dt_ioctl (TYPE_1__*,int /*<<< orphan*/ ,TYPE_6__*) ; 
 int dt_set_errno (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int dtrace_stop (TYPE_1__*) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ gethrtime () ; 

int
dtrace_status(dtrace_hdl_t *dtp)
{
	int gen = dtp->dt_statusgen;
	dtrace_optval_t interval = dtp->dt_options[DTRACEOPT_STATUSRATE];
	hrtime_t now = gethrtime();

	if (!dtp->dt_active)
		return (DTRACE_STATUS_NONE);

	if (dtp->dt_stopped)
		return (DTRACE_STATUS_STOPPED);

	if (dtp->dt_laststatus != 0) {
		if (now - dtp->dt_laststatus < interval)
			return (DTRACE_STATUS_NONE);

		dtp->dt_laststatus += interval;
	} else {
		dtp->dt_laststatus = now;
	}

	if (dt_ioctl(dtp, DTRACEIOC_STATUS, &dtp->dt_status[gen]) == -1)
		return (dt_set_errno(dtp, errno));

	dtp->dt_statusgen ^= 1;

	if (dt_handle_status(dtp, &dtp->dt_status[dtp->dt_statusgen],
	    &dtp->dt_status[gen]) == -1)
		return (-1);

	if (dtp->dt_status[gen].dtst_exiting) {
		if (!dtp->dt_stopped)
			(void) dtrace_stop(dtp);

		return (DTRACE_STATUS_EXITED);
	}

	if (dtp->dt_status[gen].dtst_filled == 0)
		return (DTRACE_STATUS_OKAY);

	if (dtp->dt_options[DTRACEOPT_BUFPOLICY] != DTRACEOPT_BUFPOLICY_FILL)
		return (DTRACE_STATUS_OKAY);

	if (!dtp->dt_stopped) {
		if (dtrace_stop(dtp) == -1)
			return (-1);
	}

	return (DTRACE_STATUS_FILLED);
}