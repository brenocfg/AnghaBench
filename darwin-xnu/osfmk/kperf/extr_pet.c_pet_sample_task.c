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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  scalar_t__ thread_t ;
typedef  int /*<<< orphan*/  task_t ;
struct kperf_context {int cur_pid; int /*<<< orphan*/  cur_task; } ;
typedef  scalar_t__ kern_return_t ;
struct TYPE_2__ {int logical_cpu_max; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUF_INFO (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  BUF_VERB (int,...) ; 
 int DBG_FUNC_END ; 
 int DBG_FUNC_START ; 
 int /*<<< orphan*/  ERR_THREAD ; 
 scalar_t__ KERN_SUCCESS ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT_OWNED ; 
 int /*<<< orphan*/  PERF_PET_ERROR ; 
 int PERF_PET_SAMPLE_TASK ; 
 int /*<<< orphan*/  SAMPLE_FLAG_TASK_ONLY ; 
 scalar_t__ THREAD_NULL ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  kernel_task ; 
 scalar_t__ kperf_action_has_task (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kperf_action_has_thread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kperf_sample (int /*<<< orphan*/ ,struct kperf_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__* kperf_tid_on_cpus ; 
 int /*<<< orphan*/  lck_mtx_assert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ machine_info ; 
 int /*<<< orphan*/  pet_action_id ; 
 int /*<<< orphan*/  pet_lock ; 
 int /*<<< orphan*/  pet_sample ; 
 int /*<<< orphan*/  pet_sample_thread (int,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__* pet_threads ; 
 unsigned int pet_threads_count ; 
 scalar_t__ pet_threads_prepare (int /*<<< orphan*/ ) ; 
 int task_pid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  task_resume_internal (int /*<<< orphan*/ ) ; 
 scalar_t__ task_suspend_internal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_deallocate (scalar_t__) ; 
 scalar_t__ thread_tid (scalar_t__) ; 

__attribute__((used)) static void
pet_sample_task(task_t task, uint32_t idle_rate)
{
	lck_mtx_assert(pet_lock, LCK_MTX_ASSERT_OWNED);

	BUF_VERB(PERF_PET_SAMPLE_TASK | DBG_FUNC_START);

	int pid = task_pid(task);
	if (kperf_action_has_task(pet_action_id)) {
		struct kperf_context ctx = {
			.cur_task = task,
			.cur_pid = pid,
		};

		kperf_sample(pet_sample, &ctx, pet_action_id, SAMPLE_FLAG_TASK_ONLY);
	}

	if (!kperf_action_has_thread(pet_action_id)) {
		BUF_VERB(PERF_PET_SAMPLE_TASK | DBG_FUNC_END);
		return;
	}

	kern_return_t kr = KERN_SUCCESS;

	/*
	 * Suspend the task to see an atomic snapshot of all its threads.  This
	 * is expensive, and disruptive.
	 */
	bool needs_suspend = task != kernel_task;
	if (needs_suspend) {
		kr = task_suspend_internal(task);
		if (kr != KERN_SUCCESS) {
			BUF_VERB(PERF_PET_SAMPLE_TASK | DBG_FUNC_END, 1);
			return;
		}
		needs_suspend = true;
	}

	kr = pet_threads_prepare(task);
	if (kr != KERN_SUCCESS) {
		BUF_INFO(PERF_PET_ERROR, ERR_THREAD, kr);
		goto out;
	}

	for (unsigned int i = 0; i < pet_threads_count; i++) {
		thread_t thread = pet_threads[i];
		assert(thread != THREAD_NULL);

		/*
		 * Do not sample the thread if it was on a CPU when the timer fired.
		 */
		int cpu = 0;
		for (cpu = 0; cpu < machine_info.logical_cpu_max; cpu++) {
			if (kperf_tid_on_cpus[cpu] == thread_tid(thread)) {
				break;
			}
		}

		/* the thread was not on a CPU */
		if (cpu == machine_info.logical_cpu_max) {
			pet_sample_thread(pid, task, thread, idle_rate);
		}

		thread_deallocate(pet_threads[i]);
	}

out:
	if (needs_suspend) {
		task_resume_internal(task);
	}

	BUF_VERB(PERF_PET_SAMPLE_TASK | DBG_FUNC_END, pet_threads_count);
}