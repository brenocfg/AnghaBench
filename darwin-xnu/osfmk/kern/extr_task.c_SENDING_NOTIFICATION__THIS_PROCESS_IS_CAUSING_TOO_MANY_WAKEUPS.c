#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  TYPE_1__* task_t ;
struct ledger_entry_info {int lei_balance; int lei_last_refill; int lei_limit; int lei_refill_period; } ;
typedef  scalar_t__ mach_exception_data_type_t ;
typedef  int kern_return_t ;
typedef  int boolean_t ;
struct TYPE_8__ {int /*<<< orphan*/  interrupt_wakeups; } ;
struct TYPE_7__ {int rusage_cpu_flags; int /*<<< orphan*/  ledger; int /*<<< orphan*/ * bsd_info; } ;

/* Variables and functions */
 int EXCEPTION_CODE_MAX ; 
 int /*<<< orphan*/  EXC_RESOURCE ; 
 int /*<<< orphan*/  EXC_RESOURCE_CPUMONITOR_ENCODE_OBSERVATION_INTERVAL (scalar_t__,int) ; 
 int /*<<< orphan*/  EXC_RESOURCE_CPUMONITOR_ENCODE_WAKEUPS_OBSERVED (scalar_t__,int) ; 
 int /*<<< orphan*/  EXC_RESOURCE_CPUMONITOR_ENCODE_WAKEUPS_PERMITTED (scalar_t__,int) ; 
 int /*<<< orphan*/  EXC_RESOURCE_ENCODE_FLAVOR (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EXC_RESOURCE_ENCODE_TYPE (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FLAVOR_WAKEUPS_MONITOR ; 
 int NSEC_PER_SEC ; 
 int /*<<< orphan*/  OS_LOG_DEFAULT ; 
 int /*<<< orphan*/  RESOURCE_TYPE_WAKEUPS ; 
 int /*<<< orphan*/  RMON_CPUWAKES_VIOLATED ; 
 int TASK_RUSECPU_FLAGS_FATAL_WAKEUPSMON ; 
 int /*<<< orphan*/  WAKEMON_DISABLE ; 
 scalar_t__ audio_active ; 
 TYPE_1__* current_task () ; 
 scalar_t__ disable_exc_resource ; 
 int /*<<< orphan*/  exception_triage (int /*<<< orphan*/ ,scalar_t__*,int) ; 
 int /*<<< orphan*/  kRNFatalLimitFlag ; 
 int /*<<< orphan*/  ledger_get_entry_info (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ledger_entry_info*) ; 
 int /*<<< orphan*/  os_log (int /*<<< orphan*/ ,char*,char const*,int,...) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 char* proc_name_address (int /*<<< orphan*/ *) ; 
 int proc_selfpid () ; 
 int /*<<< orphan*/  send_cpu_wakes_violation ; 
 int send_resource_violation (int /*<<< orphan*/ ,TYPE_1__*,struct ledger_entry_info*,int /*<<< orphan*/ ) ; 
 TYPE_4__ task_ledgers ; 
 int /*<<< orphan*/  task_terminate_internal (TYPE_1__*) ; 
 int /*<<< orphan*/  task_wakeups_monitor_ctl (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_resource_violation (int /*<<< orphan*/ ,struct ledger_entry_info*) ; 

void __attribute__((noinline))
SENDING_NOTIFICATION__THIS_PROCESS_IS_CAUSING_TOO_MANY_WAKEUPS(void)
{
	task_t                      task        = current_task();
	int                         pid         = 0;
	const char                  *procname   = "unknown";
	boolean_t                   fatal;
	kern_return_t               kr;
#ifdef EXC_RESOURCE_MONITORS
	mach_exception_data_type_t  code[EXCEPTION_CODE_MAX];
#endif /* EXC_RESOURCE_MONITORS */
	struct ledger_entry_info    lei;

#ifdef MACH_BSD
	pid = proc_selfpid();
	if (task->bsd_info != NULL)
		procname = proc_name_address(current_task()->bsd_info);
#endif

	ledger_get_entry_info(task->ledger, task_ledgers.interrupt_wakeups, &lei);

	/*
	 * Disable the exception notification so we don't overwhelm
	 * the listener with an endless stream of redundant exceptions.
	 * TODO: detect whether another thread is already reporting the violation.
	 */
	uint32_t flags = WAKEMON_DISABLE;
	task_wakeups_monitor_ctl(task, &flags, NULL);

	fatal = task->rusage_cpu_flags & TASK_RUSECPU_FLAGS_FATAL_WAKEUPSMON;
	trace_resource_violation(RMON_CPUWAKES_VIOLATED, &lei);
	os_log(OS_LOG_DEFAULT, "process %s[%d] caught waking the CPU %llu times "
	       "over ~%llu seconds, averaging %llu wakes / second and "
	       "violating a %slimit of %llu wakes over %llu seconds.\n",
	       procname, pid,
	       lei.lei_balance, lei.lei_last_refill / NSEC_PER_SEC,
		   lei.lei_last_refill == 0 ? 0 :
				(NSEC_PER_SEC * lei.lei_balance / lei.lei_last_refill),
	       fatal ? "FATAL " : "",
		   lei.lei_limit, lei.lei_refill_period / NSEC_PER_SEC);

	kr = send_resource_violation(send_cpu_wakes_violation, task, &lei,
	                             fatal ? kRNFatalLimitFlag : 0);
	if (kr) {
		printf("send_resource_violation(CPU wakes, ...): error %#x\n", kr);
	}

#ifdef EXC_RESOURCE_MONITORS
	if (disable_exc_resource) {
		printf("process %s[%d] caught causing excessive wakeups. EXC_RESOURCE "
			"supressed by a boot-arg\n", procname, pid);
		return;
	}
	if (audio_active) {
		os_log(OS_LOG_DEFAULT, "process %s[%d] caught causing excessive wakeups. EXC_RESOURCE "
		       "supressed due to audio playback\n", procname, pid);
		return;
	}
	if (lei.lei_last_refill == 0) {
		os_log(OS_LOG_DEFAULT, "process %s[%d] caught causing excessive wakeups. EXC_RESOURCE "
		       "supressed due to lei.lei_last_refill = 0 \n", procname, pid);
	}

	code[0] = code[1] = 0;
	EXC_RESOURCE_ENCODE_TYPE(code[0], RESOURCE_TYPE_WAKEUPS);
	EXC_RESOURCE_ENCODE_FLAVOR(code[0], FLAVOR_WAKEUPS_MONITOR);
	EXC_RESOURCE_CPUMONITOR_ENCODE_WAKEUPS_PERMITTED(code[0],
	                    NSEC_PER_SEC * lei.lei_limit / lei.lei_refill_period);
	EXC_RESOURCE_CPUMONITOR_ENCODE_OBSERVATION_INTERVAL(code[0],
	                    lei.lei_last_refill);
	EXC_RESOURCE_CPUMONITOR_ENCODE_WAKEUPS_OBSERVED(code[1],
	                    NSEC_PER_SEC * lei.lei_balance / lei.lei_last_refill);
	exception_triage(EXC_RESOURCE, code, EXCEPTION_CODE_MAX);
#endif /* EXC_RESOURCE_MONITORS */

	if (fatal) {
		task_terminate_internal(task);
	}
}