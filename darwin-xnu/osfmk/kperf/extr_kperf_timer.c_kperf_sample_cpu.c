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
typedef  int /*<<< orphan*/  thread_t ;
typedef  int /*<<< orphan*/  task_t ;
struct kperf_timer {int /*<<< orphan*/  pending_cpus; int /*<<< orphan*/  actionid; } ;
struct kperf_sample {int /*<<< orphan*/  sample_time; } ;
struct kperf_context {unsigned int trigger_id; int /*<<< orphan*/  cur_thread; int /*<<< orphan*/  trigger_type; int /*<<< orphan*/  cur_pid; int /*<<< orphan*/  cur_task; } ;
struct TYPE_2__ {int logical_cpu_max; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUF_DATA (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BUF_INFO (int,int) ; 
 int DBG_FUNC_END ; 
 int DBG_FUNC_START ; 
 unsigned int KPERF_SAMPLING_OFF ; 
 unsigned int KPERF_SAMPLING_SHUTDOWN ; 
 int PERF_TM_HNDLR ; 
 int SAMPLE_FLAG_ONLY_SYSTEM ; 
 int SAMPLE_FLAG_PEND_USER ; 
 int SAMPLE_FLAG_SYSTEM ; 
 int SAMPLE_OFF ; 
 int SAMPLE_SHUTDOWN ; 
 int /*<<< orphan*/  TRIGGER_TYPE_TIMER ; 
 int UINT64_C (int) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_fetch_and_explicit (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int cpu_number () ; 
 int /*<<< orphan*/  current_thread () ; 
 int /*<<< orphan*/  get_threadtask (int /*<<< orphan*/ ) ; 
 struct kperf_sample* kperf_intr_sample_buffer () ; 
 int kperf_sample (struct kperf_sample*,struct kperf_context*,int /*<<< orphan*/ ,int) ; 
 unsigned int kperf_sampling_status () ; 
 int /*<<< orphan*/ * kperf_tid_on_cpus ; 
 int /*<<< orphan*/  kperf_timerv ; 
 int /*<<< orphan*/  mach_absolute_time () ; 
 TYPE_1__ machine_info ; 
 int /*<<< orphan*/  memory_order_relaxed ; 
 scalar_t__ pet_timer_id ; 
 int /*<<< orphan*/  task_pid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_tid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
kperf_sample_cpu(struct kperf_timer *timer, bool system_sample,
		bool only_system)
{
	assert(timer != NULL);

	/* Always cut a tracepoint to show a sample event occurred */
	BUF_DATA(PERF_TM_HNDLR | DBG_FUNC_START, 0);

	int ncpu = cpu_number();

	struct kperf_sample *intbuf = kperf_intr_sample_buffer();
#if DEVELOPMENT || DEBUG
	intbuf->sample_time = mach_absolute_time();
#endif /* DEVELOPMENT || DEBUG */

	/* On a timer, we can see the "real" current thread */
	thread_t thread = current_thread();
	task_t task = get_threadtask(thread);
	struct kperf_context ctx = {
		.cur_thread = thread,
		.cur_task = task,
		.cur_pid = task_pid(task),
		.trigger_type = TRIGGER_TYPE_TIMER,
		.trigger_id = (unsigned int)(timer - kperf_timerv),
	};

	if (ctx.trigger_id == pet_timer_id && ncpu < machine_info.logical_cpu_max) {
		kperf_tid_on_cpus[ncpu] = thread_tid(ctx.cur_thread);
	}

	/* make sure sampling is on */
	unsigned int status = kperf_sampling_status();
	if (status == KPERF_SAMPLING_OFF) {
		BUF_INFO(PERF_TM_HNDLR | DBG_FUNC_END, SAMPLE_OFF);
		return;
	} else if (status == KPERF_SAMPLING_SHUTDOWN) {
		BUF_INFO(PERF_TM_HNDLR | DBG_FUNC_END, SAMPLE_SHUTDOWN);
		return;
	}

	/* call the action -- kernel-only from interrupt, pend user */
	int r = kperf_sample(intbuf, &ctx, timer->actionid,
			SAMPLE_FLAG_PEND_USER | (system_sample ? SAMPLE_FLAG_SYSTEM : 0) |
			(only_system ? SAMPLE_FLAG_ONLY_SYSTEM : 0));

	/* end tracepoint is informational */
	BUF_INFO(PERF_TM_HNDLR | DBG_FUNC_END, r);

	(void)atomic_fetch_and_explicit(&timer->pending_cpus,
			~(UINT64_C(1) << ncpu), memory_order_relaxed);
}