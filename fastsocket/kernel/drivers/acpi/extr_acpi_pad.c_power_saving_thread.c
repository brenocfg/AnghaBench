#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct sched_param {int sched_priority; } ;
struct TYPE_2__ {int /*<<< orphan*/  status; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_EVT_NOTIFY_BROADCAST_ENTER ; 
 int /*<<< orphan*/  CLOCK_EVT_NOTIFY_BROADCAST_EXIT ; 
 int HZ ; 
 int /*<<< orphan*/  SCHED_RR ; 
 int /*<<< orphan*/  TS_POLLING ; 
 int /*<<< orphan*/  __monitor (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __mwait (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  clockevents_notify (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  current ; 
 TYPE_1__* current_thread_info () ; 
 int /*<<< orphan*/  exit_round_robin (unsigned int) ; 
 int idle_pct ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  kthread_should_stop () ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  local_irq_enable () ; 
 int /*<<< orphan*/  mark_tsc_unstable (char*) ; 
 int /*<<< orphan*/  need_resched () ; 
 int /*<<< orphan*/  power_saving_mwait_eax ; 
 int /*<<< orphan*/  round_robin_cpu (unsigned int) ; 
 int round_robin_time ; 
 int /*<<< orphan*/  sched_setscheduler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sched_param*) ; 
 int /*<<< orphan*/  schedule_timeout_killable (int) ; 
 int /*<<< orphan*/  smp_mb () ; 
 int smp_processor_id () ; 
 int /*<<< orphan*/  start_critical_timings () ; 
 int /*<<< orphan*/  stop_critical_timings () ; 
 int /*<<< orphan*/  try_to_freeze () ; 
 scalar_t__ tsc_detected_unstable ; 
 int tsc_marked_unstable ; 

__attribute__((used)) static int power_saving_thread(void *data)
{
	struct sched_param param = {.sched_priority = 1};
	int do_sleep;
	unsigned int tsk_index = (unsigned long)data;
	u64 last_jiffies = 0;

	sched_setscheduler(current, SCHED_RR, &param);

	while (!kthread_should_stop()) {
		int cpu;
		u64 expire_time;

		try_to_freeze();

		/* round robin to cpus */
		if (last_jiffies + round_robin_time * HZ < jiffies) {
			last_jiffies = jiffies;
			round_robin_cpu(tsk_index);
		}

		do_sleep = 0;

		current_thread_info()->status &= ~TS_POLLING;
		/*
		 * TS_POLLING-cleared state must be visible before we test
		 * NEED_RESCHED:
		 */
		smp_mb();

		expire_time = jiffies + HZ * (100 - idle_pct) / 100;

		while (!need_resched()) {
			if (tsc_detected_unstable && !tsc_marked_unstable) {
				/* TSC could halt in idle, so notify users */
				mark_tsc_unstable("TSC halts in idle");
				tsc_marked_unstable = 1;
			}
			local_irq_disable();
			cpu = smp_processor_id();
			clockevents_notify(CLOCK_EVT_NOTIFY_BROADCAST_ENTER,
				&cpu);
			stop_critical_timings();

			__monitor((void *)&current_thread_info()->flags, 0, 0);
			smp_mb();
			if (!need_resched())
				__mwait(power_saving_mwait_eax, 1);

			start_critical_timings();
			clockevents_notify(CLOCK_EVT_NOTIFY_BROADCAST_EXIT,
				&cpu);
			local_irq_enable();

			if (jiffies > expire_time) {
				do_sleep = 1;
				break;
			}
		}

		current_thread_info()->status |= TS_POLLING;

		/*
		 * current sched_rt has threshold for rt task running time.
		 * When a rt task uses 95% CPU time, the rt thread will be
		 * scheduled out for 5% CPU time to not starve other tasks. But
		 * the mechanism only works when all CPUs have RT task running,
		 * as if one CPU hasn't RT task, RT task from other CPUs will
		 * borrow CPU time from this CPU and cause RT task use > 95%
		 * CPU time. To make 'avoid staration' work, takes a nap here.
		 */
		if (do_sleep)
			schedule_timeout_killable(HZ * idle_pct / 100);
	}

	exit_round_robin(tsk_index);
	return 0;
}