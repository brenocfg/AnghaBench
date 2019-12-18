#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* proc_t ;
typedef  TYPE_2__* os_reason_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_9__ {int /*<<< orphan*/  osr_flags; } ;
struct TYPE_8__ {int /*<<< orphan*/  p_pid; } ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  JETSAM_REASON_MEMORY_PERPROCESSLIMIT ; 
 int /*<<< orphan*/  OS_LOG_DEFAULT ; 
 int /*<<< orphan*/  OS_REASON_FLAG_GENERATE_CRASH_REPORT ; 
 int /*<<< orphan*/  OS_REASON_JETSAM ; 
 TYPE_2__* OS_REASON_NULL ; 
 scalar_t__ TRUE ; 
 scalar_t__ corpse_for_fatal_memkill ; 
 TYPE_1__* current_proc () ; 
 int /*<<< orphan*/  kMemorystatusKilledPerProcessLimit ; 
 scalar_t__ memorystatus_hwm_candidates ; 
 scalar_t__ memorystatus_kill_process_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ memorystatus_warn_process (int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  os_log (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 TYPE_2__* os_reason_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 
 scalar_t__ proc_send_synchronous_EXC_RESOURCE (TYPE_1__*) ; 

void
memorystatus_on_ledger_footprint_exceeded(boolean_t warning, boolean_t memlimit_is_active, boolean_t memlimit_is_fatal)
{
	os_reason_t jetsam_reason = OS_REASON_NULL;

	proc_t p = current_proc();

#if VM_PRESSURE_EVENTS
	if (warning == TRUE) {
		/*
		 * This is a warning path which implies that the current process is close, but has
		 * not yet exceeded its per-process memory limit.
		 */
		if (memorystatus_warn_process(p->p_pid, memlimit_is_active, memlimit_is_fatal,  FALSE /* not exceeded */) != TRUE) {
			/* Print warning, since it's possible that task has not registered for pressure notifications */
			os_log(OS_LOG_DEFAULT, "memorystatus_on_ledger_footprint_exceeded: failed to warn the current task (%d exiting, or no handler registered?).\n", p->p_pid);
		}
		return;
	}
#endif /* VM_PRESSURE_EVENTS */

	if (memlimit_is_fatal) {
		/*
		 * If this process has no high watermark or has a fatal task limit, then we have been invoked because the task
		 * has violated either the system-wide per-task memory limit OR its own task limit.
		 */
		jetsam_reason = os_reason_create(OS_REASON_JETSAM, JETSAM_REASON_MEMORY_PERPROCESSLIMIT);
		if (jetsam_reason == NULL) {
			printf("task_exceeded footprint: failed to allocate jetsam reason\n");
		} else if (corpse_for_fatal_memkill != 0 && proc_send_synchronous_EXC_RESOURCE(p) == FALSE) {
			/* Set OS_REASON_FLAG_GENERATE_CRASH_REPORT to generate corpse */
			jetsam_reason->osr_flags |= OS_REASON_FLAG_GENERATE_CRASH_REPORT;
		}

		if (memorystatus_kill_process_sync(p->p_pid, kMemorystatusKilledPerProcessLimit, jetsam_reason) != TRUE) {
			printf("task_exceeded_footprint: failed to kill the current task (exiting?).\n");
		}
	} else {
		/*
		 * HWM offender exists. Done without locks or synchronization.
		 * See comment near its declaration for more details.
		 */
		memorystatus_hwm_candidates = TRUE;

#if VM_PRESSURE_EVENTS
		/*
		 * The current process is not in the warning path.
		 * This path implies the current process has exceeded a non-fatal (soft) memory limit.
		 * Failure to send note is ignored here.
		 */
		(void)memorystatus_warn_process(p->p_pid, memlimit_is_active, memlimit_is_fatal, TRUE /* exceeded */);

#endif /* VM_PRESSURE_EVENTS */
	}
}