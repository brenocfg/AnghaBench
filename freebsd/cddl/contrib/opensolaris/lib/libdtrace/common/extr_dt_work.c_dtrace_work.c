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
typedef  scalar_t__ dtrace_workstatus_t ;
typedef  scalar_t__ dtrace_optval_t ;
struct TYPE_6__ {scalar_t__* dt_options; int /*<<< orphan*/  dt_lastagg; int /*<<< orphan*/  dt_lastswitch; } ;
typedef  TYPE_1__ dtrace_hdl_t ;
typedef  int /*<<< orphan*/  dtrace_consume_rec_f ;
typedef  int /*<<< orphan*/  dtrace_consume_probe_f ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 size_t DTRACEOPT_BUFPOLICY ; 
 scalar_t__ DTRACEOPT_BUFPOLICY_SWITCH ; 
#define  DTRACE_STATUS_EXITED 132 
#define  DTRACE_STATUS_FILLED 131 
#define  DTRACE_STATUS_NONE 130 
#define  DTRACE_STATUS_OKAY 129 
#define  DTRACE_STATUS_STOPPED 128 
 scalar_t__ DTRACE_WORKSTATUS_DONE ; 
 scalar_t__ DTRACE_WORKSTATUS_ERROR ; 
 scalar_t__ DTRACE_WORKSTATUS_OKAY ; 
 int /*<<< orphan*/  assert (int) ; 
 int dtrace_aggregate_snap (TYPE_1__*) ; 
 int dtrace_consume (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*) ; 
 int dtrace_status (TYPE_1__*) ; 

dtrace_workstatus_t
dtrace_work(dtrace_hdl_t *dtp, FILE *fp,
    dtrace_consume_probe_f *pfunc, dtrace_consume_rec_f *rfunc, void *arg)
{
	int status = dtrace_status(dtp);
	dtrace_optval_t policy = dtp->dt_options[DTRACEOPT_BUFPOLICY];
	dtrace_workstatus_t rval;

	switch (status) {
	case DTRACE_STATUS_EXITED:
	case DTRACE_STATUS_FILLED:
	case DTRACE_STATUS_STOPPED:
		/*
		 * Tracing is stopped.  We now want to force dtrace_consume()
		 * and dtrace_aggregate_snap() to proceed, regardless of
		 * switchrate and aggrate.  We do this by clearing the times.
		 */
		dtp->dt_lastswitch = 0;
		dtp->dt_lastagg = 0;
		rval = DTRACE_WORKSTATUS_DONE;
		break;

	case DTRACE_STATUS_NONE:
	case DTRACE_STATUS_OKAY:
		rval = DTRACE_WORKSTATUS_OKAY;
		break;

	case -1:
		return (DTRACE_WORKSTATUS_ERROR);
	}

	if ((status == DTRACE_STATUS_NONE || status == DTRACE_STATUS_OKAY) &&
	    policy != DTRACEOPT_BUFPOLICY_SWITCH) {
		/*
		 * There either isn't any status or things are fine -- and
		 * this is a "ring" or "fill" buffer.  We don't want to consume
		 * any of the trace data or snapshot the aggregations; we just
		 * return.
		 */
		assert(rval == DTRACE_WORKSTATUS_OKAY);
		return (rval);
	}

	if (dtrace_aggregate_snap(dtp) == -1)
		return (DTRACE_WORKSTATUS_ERROR);

	if (dtrace_consume(dtp, fp, pfunc, rfunc, arg) == -1)
		return (DTRACE_WORKSTATUS_ERROR);

	return (rval);
}