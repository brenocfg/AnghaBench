#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_9__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  unsigned long long uint64_t ;
typedef  int uint32_t ;
struct TYPE_17__ {int seconds; int microseconds; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ time_value_t ;
typedef  TYPE_2__* thread_t ;
typedef  TYPE_3__* task_t ;
struct ledger_entry_info {unsigned long long lei_balance; unsigned long long lei_last_refill; unsigned long long lei_limit; int /*<<< orphan*/  lei_refill_period; int /*<<< orphan*/  lei_debit; int /*<<< orphan*/  lei_credit; } ;
typedef  int kern_return_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_20__ {int /*<<< orphan*/  cpu_time; } ;
struct TYPE_19__ {int rusage_cpu_flags; } ;
struct TYPE_18__ {unsigned long long thread_id; scalar_t__ t_threadledger; } ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int KERN_INVALID_ARGUMENT ; 
 scalar_t__ LEDGER_NULL ; 
 unsigned long long NSEC_PER_SEC ; 
 int /*<<< orphan*/  RMON_CPUUSAGE_VIOLATED ; 
 int TASK_RUSECPU_FLAGS_FATAL_CPUMON ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  absolutetime_to_nanoseconds (unsigned long long,unsigned long long*) ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_3__* current_task () ; 
 TYPE_2__* current_thread () ; 
 int /*<<< orphan*/  kRNFatalLimitFlag ; 
 int /*<<< orphan*/  ledger_get_entry_info (scalar_t__,int /*<<< orphan*/ ,struct ledger_entry_info*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  send_cpu_usage_violation ; 
 int send_resource_violation (int /*<<< orphan*/ ,TYPE_3__*,struct ledger_entry_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  task_lock (TYPE_3__*) ; 
 int task_suspend_cpumon (TYPE_3__*) ; 
 int /*<<< orphan*/  task_terminate_internal (TYPE_3__*) ; 
 int /*<<< orphan*/  task_unlock (TYPE_3__*) ; 
 int /*<<< orphan*/  thread_get_cpulimit (int*,int*,unsigned long long*) ; 
 TYPE_9__ thread_ledgers ; 
 int /*<<< orphan*/  thread_read_times (TYPE_2__*,TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  time_value_add (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  trace_resource_violation (int /*<<< orphan*/ ,struct ledger_entry_info*) ; 

void __attribute__((noinline))
SENDING_NOTIFICATION__THIS_THREAD_IS_CONSUMING_TOO_MUCH_CPU(void)
{
	int          pid                = 0;
	task_t		 task				= current_task();
	thread_t     thread             = current_thread();
	uint64_t     tid                = thread->thread_id;
	const char	 *procname          = "unknown";
	time_value_t thread_total_time  = {0, 0};
	time_value_t thread_system_time;
	time_value_t thread_user_time;
	int          action;
	uint8_t      percentage;
	uint32_t     usage_percent = 0;
	uint32_t     interval_sec;
	uint64_t     interval_ns;
	uint64_t     balance_ns;
	boolean_t	 fatal = FALSE;
	boolean_t	 send_exc_resource = TRUE; /* in addition to RESOURCE_NOTIFY */
	kern_return_t	kr;

#ifdef EXC_RESOURCE_MONITORS
	mach_exception_data_type_t	code[EXCEPTION_CODE_MAX];
#endif /* EXC_RESOURCE_MONITORS */
	struct ledger_entry_info	lei;

	assert(thread->t_threadledger != LEDGER_NULL);

	/*
	 * Extract the fatal bit and suspend the monitor (which clears the bit).
	 */
	task_lock(task);
	if (task->rusage_cpu_flags & TASK_RUSECPU_FLAGS_FATAL_CPUMON) {
		fatal = TRUE;
		send_exc_resource = TRUE;
	}
	/* Only one thread can be here at a time.  Whichever makes it through
	   first will successfully suspend the monitor and proceed to send the
	   notification.  Other threads will get an error trying to suspend the
	   monitor and give up on sending the notification.  In the first release,
	   the monitor won't be resumed for a number of seconds, but we may
	   eventually need to handle low-latency resume.
	 */
	kr = task_suspend_cpumon(task);
	task_unlock(task);
	if (kr == KERN_INVALID_ARGUMENT)	return;

#ifdef MACH_BSD
	pid = proc_selfpid();
	if (task->bsd_info != NULL) {
		procname = proc_name_address(task->bsd_info);
	}
#endif

	thread_get_cpulimit(&action, &percentage, &interval_ns);

	interval_sec = (uint32_t)(interval_ns / NSEC_PER_SEC);

	thread_read_times(thread, &thread_user_time, &thread_system_time, NULL);
	time_value_add(&thread_total_time, &thread_user_time);
	time_value_add(&thread_total_time, &thread_system_time);
	ledger_get_entry_info(thread->t_threadledger, thread_ledgers.cpu_time, &lei);

	/* credit/debit/balance/limit are in absolute time units;
	   the refill info is in nanoseconds. */
	absolutetime_to_nanoseconds(lei.lei_balance, &balance_ns);
	if (lei.lei_last_refill > 0) {
		usage_percent = (uint32_t)((balance_ns*100ULL) / lei.lei_last_refill);
	}

	/* TODO: show task total runtime (via TASK_ABSOLUTETIME_INFO)? */
	printf("process %s[%d] thread %llu caught burning CPU! "
	       "It used more than %d%% CPU over %u seconds "
	       "(actual recent usage: %d%% over ~%llu seconds).  "
	       "Thread lifetime cpu usage %d.%06ds, (%d.%06d user, %d.%06d sys) "
	       "ledger balance: %lld mabs credit: %lld mabs debit: %lld mabs "
	       "limit: %llu mabs period: %llu ns last refill: %llu ns%s.\n",
	       procname, pid, tid,
	       percentage, interval_sec,
	       usage_percent,
	       (lei.lei_last_refill + NSEC_PER_SEC/2) / NSEC_PER_SEC,
	       thread_total_time.seconds, thread_total_time.microseconds,
	       thread_user_time.seconds, thread_user_time.microseconds,
	       thread_system_time.seconds,thread_system_time.microseconds,
	       lei.lei_balance, lei.lei_credit, lei.lei_debit,
	       lei.lei_limit, lei.lei_refill_period, lei.lei_last_refill,
	       (fatal ? " [fatal violation]" : ""));

	/*
	   For now, send RESOURCE_NOTIFY in parallel with EXC_RESOURCE.  Once
	   we have logging parity, we will stop sending EXC_RESOURCE (24508922).
	 */

	/* RESOURCE_NOTIFY MIG specifies nanoseconds of CPU time */
	lei.lei_balance = balance_ns;
	absolutetime_to_nanoseconds(lei.lei_limit, &lei.lei_limit);
	trace_resource_violation(RMON_CPUUSAGE_VIOLATED, &lei);
	kr = send_resource_violation(send_cpu_usage_violation, task, &lei,
								 fatal ? kRNFatalLimitFlag : 0);
	if (kr) {
		printf("send_resource_violation(CPU usage, ...): error %#x\n", kr);
	}

#ifdef EXC_RESOURCE_MONITORS
	if (send_exc_resource) {
		if (disable_exc_resource) {
			printf("process %s[%d] thread %llu caught burning CPU! "
				   "EXC_RESOURCE%s supressed by a boot-arg\n",
				   procname, pid, tid, fatal ? " (and termination)" : "");
			return;
		}

		if (audio_active) {
			printf("process %s[%d] thread %llu caught burning CPU! "
			   "EXC_RESOURCE & termination supressed due to audio playback\n",
				   procname, pid, tid);
			return;
		}
	}


	if (send_exc_resource) {
		code[0] = code[1] = 0;
		EXC_RESOURCE_ENCODE_TYPE(code[0], RESOURCE_TYPE_CPU);
		if (fatal) {
			EXC_RESOURCE_ENCODE_FLAVOR(code[0], FLAVOR_CPU_MONITOR_FATAL);
		}else {
			EXC_RESOURCE_ENCODE_FLAVOR(code[0], FLAVOR_CPU_MONITOR);
		}
		EXC_RESOURCE_CPUMONITOR_ENCODE_INTERVAL(code[0], interval_sec);
		EXC_RESOURCE_CPUMONITOR_ENCODE_PERCENTAGE(code[0], percentage);
		EXC_RESOURCE_CPUMONITOR_ENCODE_PERCENTAGE(code[1], usage_percent);
		exception_triage(EXC_RESOURCE, code, EXCEPTION_CODE_MAX);
	}
#endif /* EXC_RESOURCE_MONITORS */

	if (fatal) {
#if CONFIG_JETSAM
		jetsam_on_ledger_cpulimit_exceeded();
#else
		task_terminate_internal(task);
#endif
	}
}