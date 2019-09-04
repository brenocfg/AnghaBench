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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  thread_t ;
typedef  int /*<<< orphan*/  task_t ;
struct kperf_sample {int dummy; } ;
struct kperf_context {int /*<<< orphan*/  cur_pid; int /*<<< orphan*/  cur_task; int /*<<< orphan*/  cur_thread; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUF_INFO (int,int,...) ; 
 int DBG_FUNC_END ; 
 int DBG_FUNC_START ; 
 int PERF_AST_HNDLR ; 
 unsigned int SAMPLER_TH_DISPATCH ; 
 unsigned int SAMPLER_TH_INFO ; 
 unsigned int SAMPLER_USTACK ; 
 int SAMPLE_CONTINUE ; 
 int T_KPERF_AST_CALLSTACK ; 
 int T_KPERF_AST_DISPATCH ; 
 int T_KPERF_GET_CALLSTACK_DEPTH (int) ; 
 int /*<<< orphan*/  get_threadtask (int /*<<< orphan*/ ) ; 
 int kperf_get_thread_flags (int /*<<< orphan*/ ) ; 
 int kperf_sample_internal (struct kperf_sample*,struct kperf_context*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct kperf_sample*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ task_did_exec (int /*<<< orphan*/ ) ; 
 scalar_t__ task_is_exec_copy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  task_pid (int /*<<< orphan*/ ) ; 

__attribute__((noinline))
void
kperf_thread_ast_handler(thread_t thread)
{
	BUF_INFO(PERF_AST_HNDLR | DBG_FUNC_START, thread, kperf_get_thread_flags(thread));

	/* ~2KB of the stack for the sample since this is called from AST */
	struct kperf_sample sbuf;
	memset(&sbuf, 0, sizeof(struct kperf_sample));

	task_t task = get_threadtask(thread);

	if (task_did_exec(task) || task_is_exec_copy(task)) {
		BUF_INFO(PERF_AST_HNDLR | DBG_FUNC_END, SAMPLE_CONTINUE);
		return;
	}

	/* make a context, take a sample */
	struct kperf_context ctx = {
		.cur_thread = thread,
		.cur_task = task,
		.cur_pid = task_pid(task),
	};

	/* decode the flags to determine what to sample */
	unsigned int sample_what = 0;
	uint32_t flags = kperf_get_thread_flags(thread);

	if (flags & T_KPERF_AST_DISPATCH) {
		sample_what |= SAMPLER_TH_DISPATCH;
	}
	if (flags & T_KPERF_AST_CALLSTACK) {
		sample_what |= SAMPLER_USTACK;
		sample_what |= SAMPLER_TH_INFO;
	}

	uint32_t ucallstack_depth = T_KPERF_GET_CALLSTACK_DEPTH(flags);

	int r = kperf_sample_internal(&sbuf, &ctx, sample_what, 0, 0, ucallstack_depth);

	BUF_INFO(PERF_AST_HNDLR | DBG_FUNC_END, r);
}