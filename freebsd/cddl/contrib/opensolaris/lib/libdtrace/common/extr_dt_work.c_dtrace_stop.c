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
struct TYPE_6__ {int dt_statusgen; int dt_stopped; int /*<<< orphan*/ * dt_status; int /*<<< orphan*/  dt_endedon; } ;
typedef  TYPE_1__ dtrace_hdl_t ;

/* Variables and functions */
 int /*<<< orphan*/  DTRACEIOC_STATUS ; 
 int /*<<< orphan*/  DTRACEIOC_STOP ; 
 int dt_handle_status (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int dt_ioctl (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int dt_set_errno (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 

int
dtrace_stop(dtrace_hdl_t *dtp)
{
	int gen = dtp->dt_statusgen;

	if (dtp->dt_stopped)
		return (0);

	if (dt_ioctl(dtp, DTRACEIOC_STOP, &dtp->dt_endedon) == -1)
		return (dt_set_errno(dtp, errno));

	dtp->dt_stopped = 1;

	/*
	 * Now that we're stopped, we're going to get status one final time.
	 */
	if (dt_ioctl(dtp, DTRACEIOC_STATUS, &dtp->dt_status[gen]) == -1)
		return (dt_set_errno(dtp, errno));

	if (dt_handle_status(dtp, &dtp->dt_status[gen ^ 1],
	    &dtp->dt_status[gen]) == -1)
		return (-1);

	return (0);
}