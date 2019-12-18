#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ hrtime_t ;
typedef  scalar_t__ dtrace_optval_t ;
struct TYPE_7__ {scalar_t__ dtbd_size; } ;
struct TYPE_9__ {int dtat_ncpus; int /*<<< orphan*/ * dtat_cpus; TYPE_1__ dtat_buf; } ;
struct TYPE_8__ {scalar_t__* dt_options; scalar_t__ dt_lastagg; int /*<<< orphan*/  dt_active; TYPE_3__ dt_aggregate; } ;
typedef  TYPE_2__ dtrace_hdl_t ;
typedef  TYPE_3__ dt_aggregate_t ;

/* Variables and functions */
 size_t DTRACEOPT_AGGRATE ; 
 int /*<<< orphan*/  EINVAL ; 
 int dt_aggregate_snap_cpu (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int dt_set_errno (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ gethrtime () ; 

int
dtrace_aggregate_snap(dtrace_hdl_t *dtp)
{
	int i, rval;
	dt_aggregate_t *agp = &dtp->dt_aggregate;
	hrtime_t now = gethrtime();
	dtrace_optval_t interval = dtp->dt_options[DTRACEOPT_AGGRATE];

	if (dtp->dt_lastagg != 0) {
		if (now - dtp->dt_lastagg < interval)
			return (0);

		dtp->dt_lastagg += interval;
	} else {
		dtp->dt_lastagg = now;
	}

	if (!dtp->dt_active)
		return (dt_set_errno(dtp, EINVAL));

	if (agp->dtat_buf.dtbd_size == 0)
		return (0);

	for (i = 0; i < agp->dtat_ncpus; i++) {
		if ((rval = dt_aggregate_snap_cpu(dtp, agp->dtat_cpus[i])))
			return (rval);
	}

	return (0);
}