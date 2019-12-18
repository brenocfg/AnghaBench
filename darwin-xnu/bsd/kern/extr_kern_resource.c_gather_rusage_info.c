#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct rusage_info_child {int /*<<< orphan*/  ri_child_elapsed_abstime; int /*<<< orphan*/  ri_child_pageins; int /*<<< orphan*/  ri_child_interrupt_wkups; int /*<<< orphan*/  ri_child_pkg_idle_wkups; int /*<<< orphan*/  ri_child_system_time; int /*<<< orphan*/  ri_child_user_time; } ;
struct TYPE_16__ {int /*<<< orphan*/  ri_proc_start_abstime; int /*<<< orphan*/  ri_uuid; int /*<<< orphan*/  ri_child_elapsed_abstime; int /*<<< orphan*/  ri_child_pageins; int /*<<< orphan*/  ri_child_interrupt_wkups; int /*<<< orphan*/  ri_child_pkg_idle_wkups; int /*<<< orphan*/  ri_child_system_time; int /*<<< orphan*/  ri_child_user_time; int /*<<< orphan*/  ri_interval_max_phys_footprint; int /*<<< orphan*/  ri_lifetime_max_phys_footprint; int /*<<< orphan*/  ri_logical_writes; } ;
typedef  TYPE_2__ rusage_info_current ;
typedef  TYPE_3__* proc_t ;
struct TYPE_17__ {TYPE_1__* p_stats; int /*<<< orphan*/  task; } ;
struct TYPE_15__ {int /*<<< orphan*/  ps_start; struct rusage_info_child ri_child; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
#define  RUSAGE_INFO_V0 132 
#define  RUSAGE_INFO_V1 131 
#define  RUSAGE_INFO_V2 130 
#define  RUSAGE_INFO_V3 129 
#define  RUSAGE_INFO_V4 128 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fill_task_billed_usage (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  fill_task_io_rusage (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  fill_task_monotonic_rusage (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  fill_task_qos_rusage (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  fill_task_rusage (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  get_task_logical_writes (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_task_phys_footprint_interval_max (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_task_phys_footprint_lifetime_max (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  proc_getexecutableuuid (TYPE_3__*,unsigned char*,int) ; 
 int /*<<< orphan*/  proc_lock (TYPE_3__*) ; 
 int /*<<< orphan*/  proc_unlock (TYPE_3__*) ; 

void
gather_rusage_info(proc_t p, rusage_info_current *ru, int flavor)
{
	struct rusage_info_child *ri_child;

	assert(p->p_stats != NULL);
	memset(ru, 0, sizeof(*ru));
	switch(flavor) {
	case RUSAGE_INFO_V4:
		ru->ri_logical_writes = get_task_logical_writes(p->task);
		ru->ri_lifetime_max_phys_footprint = get_task_phys_footprint_lifetime_max(p->task);
#if CONFIG_LEDGER_INTERVAL_MAX
		ru->ri_interval_max_phys_footprint = get_task_phys_footprint_interval_max(p->task, FALSE);
#endif
		fill_task_monotonic_rusage(p->task, ru);
	/* fall through */

	case RUSAGE_INFO_V3:
		fill_task_qos_rusage(p->task, ru);
		fill_task_billed_usage(p->task, ru);
		/* fall through */

	case RUSAGE_INFO_V2:
		fill_task_io_rusage(p->task, ru);
		/* fall through */

	case RUSAGE_INFO_V1:
		/*
		 * p->p_stats->ri_child statistics are protected under proc lock.
		 */
		proc_lock(p);
		
		ri_child = &(p->p_stats->ri_child);
		ru->ri_child_user_time = ri_child->ri_child_user_time;
		ru->ri_child_system_time = ri_child->ri_child_system_time;
		ru->ri_child_pkg_idle_wkups = ri_child->ri_child_pkg_idle_wkups;
		ru->ri_child_interrupt_wkups = ri_child->ri_child_interrupt_wkups;
		ru->ri_child_pageins = ri_child->ri_child_pageins;
		ru->ri_child_elapsed_abstime = ri_child->ri_child_elapsed_abstime;

		proc_unlock(p);
		/* fall through */

	case RUSAGE_INFO_V0:
		proc_getexecutableuuid(p, (unsigned char *)&ru->ri_uuid, sizeof (ru->ri_uuid));
		fill_task_rusage(p->task, ru);
		ru->ri_proc_start_abstime = p->p_stats->ps_start;
	}
}