#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  TYPE_1__* thread_t ;
typedef  int int32_t ;
typedef  scalar_t__ int16_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_7__ {int timer_coalesce_rt_shift; scalar_t__ timer_coalesce_rt_abstime_max; scalar_t__ timer_coalesce_bg_abstime_max; int timer_coalesce_bg_shift; int timer_coalesce_kt_shift; scalar_t__ timer_coalesce_kt_abstime_max; int timer_coalesce_fp_shift; scalar_t__ timer_coalesce_fp_abstime_max; int timer_coalesce_ts_shift; scalar_t__ timer_coalesce_ts_abstime_max; } ;
struct TYPE_6__ {scalar_t__ sched_pri; scalar_t__ sched_mode; } ;

/* Variables and functions */
 scalar_t__ BASEPRI_RTQUEUES ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ MINPRI_KERNEL ; 
 int /*<<< orphan*/  TASK_POLICY_DARWIN_BG ; 
 int /*<<< orphan*/  TCOAL_PRIO_STAT (int /*<<< orphan*/ ) ; 
 scalar_t__ TH_MODE_FIXED ; 
 scalar_t__ TH_MODE_TIMESHARE ; 
 int TIMER_CALL_SYS_BACKGROUND ; 
 int TIMER_CALL_USER_BACKGROUND ; 
 int TIMER_CALL_USER_CRITICAL ; 
 int TIMER_CALL_USER_MASK ; 
 int /*<<< orphan*/  bg_tcl ; 
 int /*<<< orphan*/  fp_tcl ; 
 int /*<<< orphan*/  kt_tcl ; 
 int /*<<< orphan*/  nc_tcl ; 
 scalar_t__ proc_get_effective_thread_policy (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qos_tcl ; 
 int /*<<< orphan*/  rt_tcl ; 
 TYPE_4__ tcoal_prio_params ; 
 scalar_t__ tcoal_qos_adjust (TYPE_1__*,int*,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ts_tcl ; 

__attribute__((used)) static void
timer_compute_leeway(thread_t cthread, int32_t urgency, int32_t *tshift, uint64_t *tmax_abstime, boolean_t *pratelimited) {
	int16_t tpri = cthread->sched_pri;
	if ((urgency & TIMER_CALL_USER_MASK) != 0) {
		if (tpri >= BASEPRI_RTQUEUES ||
		urgency == TIMER_CALL_USER_CRITICAL) {
			*tshift = tcoal_prio_params.timer_coalesce_rt_shift;
			*tmax_abstime = tcoal_prio_params.timer_coalesce_rt_abstime_max;
			TCOAL_PRIO_STAT(rt_tcl);
		} else if (proc_get_effective_thread_policy(cthread, TASK_POLICY_DARWIN_BG) ||
		(urgency == TIMER_CALL_USER_BACKGROUND)) {
			/* Determine if timer should be subjected to a lower QoS */
			if (tcoal_qos_adjust(cthread, tshift, tmax_abstime, pratelimited)) {
				if (*tmax_abstime > tcoal_prio_params.timer_coalesce_bg_abstime_max) {
					return;
				} else {
					*pratelimited = FALSE;
				}
			}
			*tshift = tcoal_prio_params.timer_coalesce_bg_shift;
			*tmax_abstime = tcoal_prio_params.timer_coalesce_bg_abstime_max;
			TCOAL_PRIO_STAT(bg_tcl);
		} else if (tpri >= MINPRI_KERNEL) {
			*tshift = tcoal_prio_params.timer_coalesce_kt_shift;
			*tmax_abstime = tcoal_prio_params.timer_coalesce_kt_abstime_max;
			TCOAL_PRIO_STAT(kt_tcl);
		} else if (cthread->sched_mode == TH_MODE_FIXED) {
			*tshift = tcoal_prio_params.timer_coalesce_fp_shift;
			*tmax_abstime = tcoal_prio_params.timer_coalesce_fp_abstime_max;
			TCOAL_PRIO_STAT(fp_tcl);
		} else if (tcoal_qos_adjust(cthread, tshift, tmax_abstime, pratelimited)) {
			TCOAL_PRIO_STAT(qos_tcl);
		} else if (cthread->sched_mode == TH_MODE_TIMESHARE) {
			*tshift = tcoal_prio_params.timer_coalesce_ts_shift;
			*tmax_abstime = tcoal_prio_params.timer_coalesce_ts_abstime_max;
			TCOAL_PRIO_STAT(ts_tcl);
		} else {
			TCOAL_PRIO_STAT(nc_tcl);
		}
	} else if (urgency == TIMER_CALL_SYS_BACKGROUND) {
		*tshift = tcoal_prio_params.timer_coalesce_bg_shift;
		*tmax_abstime = tcoal_prio_params.timer_coalesce_bg_abstime_max;
		TCOAL_PRIO_STAT(bg_tcl);
	} else {
		*tshift = tcoal_prio_params.timer_coalesce_kt_shift;
		*tmax_abstime = tcoal_prio_params.timer_coalesce_kt_abstime_max;
		TCOAL_PRIO_STAT(kt_tcl);
	}
}