#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  TYPE_1__* thread_t ;
typedef  int /*<<< orphan*/  task_t ;
struct kperf_sample {int dummy; } ;
struct kperf_context {int /*<<< orphan*/  starting_fp; int /*<<< orphan*/  trigger_type; int /*<<< orphan*/  cur_pid; int /*<<< orphan*/  cur_task; TYPE_1__* cur_thread; } ;
typedef  TYPE_2__* processor_t ;
struct TYPE_7__ {scalar_t__ kperf_last_sample_time; } ;
struct TYPE_6__ {int /*<<< orphan*/  sched_pri; int /*<<< orphan*/  system_timer; int /*<<< orphan*/  user_timer; int /*<<< orphan*/  runnable_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUF_DATA (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  PERF_LZ_CPUSAMPLE ; 
 unsigned int SAMPLE_FLAG_PEND_USER ; 
 int /*<<< orphan*/  TRIGGER_TYPE_LAZY_CPU ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_2__* current_processor () ; 
 int /*<<< orphan*/  get_threadtask (TYPE_1__*) ; 
 struct kperf_sample* kperf_intr_sample_buffer () ; 
 int /*<<< orphan*/  kperf_lazy_cpu_action ; 
 scalar_t__ kperf_lazy_cpu_time_threshold ; 
 int /*<<< orphan*/  kperf_sample (struct kperf_sample*,struct kperf_context*,int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ mach_absolute_time () ; 
 scalar_t__ ml_get_interrupts_enabled () ; 
 int /*<<< orphan*/  task_pid (int /*<<< orphan*/ ) ; 
 scalar_t__ timer_grab (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_update (int /*<<< orphan*/ *,scalar_t__) ; 

void
kperf_lazy_cpu_sample(thread_t thread, unsigned int flags, bool interrupt)
{
	assert(ml_get_interrupts_enabled() == FALSE);

	/* take a sample if this CPU's last sample time is beyond the threshold */
	processor_t processor = current_processor();
	uint64_t time_now = mach_absolute_time();
	uint64_t since_last_sample = time_now - processor->kperf_last_sample_time;
	if (since_last_sample > kperf_lazy_cpu_time_threshold) {
		processor->kperf_last_sample_time = time_now;
		timer_update(&thread->runnable_timer, time_now);
		timer_update(&thread->system_timer, time_now);

		uint64_t runnable_time = timer_grab(&thread->runnable_timer);
		uint64_t running_time = timer_grab(&thread->user_timer) +
				timer_grab(&thread->system_timer);

		BUF_DATA(PERF_LZ_CPUSAMPLE, running_time, runnable_time,
				thread->sched_pri, interrupt ? 1 : 0);

		task_t task = get_threadtask(thread);
		struct kperf_context ctx = {
			.cur_thread = thread,
			.cur_task = task,
			.cur_pid = task_pid(task),
			.trigger_type = TRIGGER_TYPE_LAZY_CPU,
			.starting_fp = 0,
		};

		struct kperf_sample *sample = kperf_intr_sample_buffer();
		if (!sample) {
			return;
		}

		kperf_sample(sample, &ctx, kperf_lazy_cpu_action,
				SAMPLE_FLAG_PEND_USER | flags);
	}
}