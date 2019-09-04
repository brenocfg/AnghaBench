#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  thread_t ;
typedef  int /*<<< orphan*/  task_t ;
struct kperf_sample {int dummy; } ;
struct kperf_context {uintptr_t* starting_fp; int /*<<< orphan*/  trigger_id; int /*<<< orphan*/  trigger_type; int /*<<< orphan*/  cur_pid; int /*<<< orphan*/  cur_task; int /*<<< orphan*/  cur_thread; } ;
typedef  int /*<<< orphan*/  kern_return_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUF_VERB (int,int /*<<< orphan*/ ) ; 
 int DBG_FUNC_END ; 
 int DBG_FUNC_START ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int PERF_KDBG_HNDLR ; 
 int /*<<< orphan*/  SAMPLE_FLAG_NON_INTERRUPT ; 
 int /*<<< orphan*/  SAMPLE_FLAG_PEND_USER ; 
 int /*<<< orphan*/  TRIGGER_TYPE_KDEBUG ; 
 int /*<<< orphan*/  current_thread () ; 
 int /*<<< orphan*/  get_threadtask (int /*<<< orphan*/ ) ; 
 struct kperf_sample* kperf_intr_sample_buffer () ; 
 int /*<<< orphan*/  kperf_kdebug_get_action () ; 
 int /*<<< orphan*/  kperf_kdebug_should_trigger (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kperf_sample (struct kperf_sample*,struct kperf_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ml_at_interrupt_context () ; 
 int ml_set_interrupts_enabled (int) ; 
 int /*<<< orphan*/  task_pid (int /*<<< orphan*/ ) ; 

void
kperf_kdebug_handler(uint32_t debugid, uintptr_t *starting_fp)
{
	uint32_t sample_flags = SAMPLE_FLAG_PEND_USER;
	struct kperf_sample *sample = NULL;
	kern_return_t kr = KERN_SUCCESS;
	int s;

	if (!kperf_kdebug_should_trigger(debugid)) {
		return;
	}

	BUF_VERB(PERF_KDBG_HNDLR | DBG_FUNC_START, debugid);

	thread_t thread = current_thread();
	task_t task = get_threadtask(thread);
	struct kperf_context ctx = {
		.cur_thread = thread,
		.cur_task = task,
		.cur_pid = task_pid(task),
		.trigger_type = TRIGGER_TYPE_KDEBUG,
		.trigger_id = 0,
	};

	s = ml_set_interrupts_enabled(0);

	sample = kperf_intr_sample_buffer();

	if (!ml_at_interrupt_context()) {
		sample_flags |= SAMPLE_FLAG_NON_INTERRUPT;
		ctx.starting_fp = starting_fp;
	}

	kr = kperf_sample(sample, &ctx, kperf_kdebug_get_action(), sample_flags);

	ml_set_interrupts_enabled(s);
	BUF_VERB(PERF_KDBG_HNDLR | DBG_FUNC_END, kr);
}