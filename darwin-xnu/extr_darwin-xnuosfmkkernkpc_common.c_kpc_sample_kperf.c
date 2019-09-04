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
struct kperf_context {int /*<<< orphan*/  trigger_id; int /*<<< orphan*/  trigger_type; int /*<<< orphan*/  cur_pid; int /*<<< orphan*/  cur_task; int /*<<< orphan*/  cur_thread; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUF_DATA (int) ; 
 int /*<<< orphan*/  BUF_INFO (int,int) ; 
 int DBG_FUNC_END ; 
 int DBG_FUNC_START ; 
 int PERF_KPC_HNDLR ; 
 int /*<<< orphan*/  SAMPLE_FLAG_PEND_USER ; 
 int /*<<< orphan*/  TRIGGER_TYPE_PMI ; 
 int /*<<< orphan*/  current_thread () ; 
 int /*<<< orphan*/  get_threadtask (int /*<<< orphan*/ ) ; 
 int kperf_sample (struct kperf_sample*,struct kperf_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  task_pid (int /*<<< orphan*/ ) ; 

void
kpc_sample_kperf(uint32_t actionid)
{
	struct kperf_sample sbuf;

	BUF_DATA(PERF_KPC_HNDLR | DBG_FUNC_START);

	thread_t thread = current_thread();
	task_t task = get_threadtask(thread);

	struct kperf_context ctx = {
		.cur_thread = thread,
		.cur_task = task,
		.cur_pid = task_pid(task),
		.trigger_type = TRIGGER_TYPE_PMI,
		.trigger_id = 0,
	};

	int r = kperf_sample(&sbuf, &ctx, actionid, SAMPLE_FLAG_PEND_USER);

	BUF_INFO(PERF_KPC_HNDLR | DBG_FUNC_END, r);
}