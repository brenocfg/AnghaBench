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
typedef  int u32 ;
struct utrace_report {int result; } ;
struct utrace_engine {int /*<<< orphan*/ * ops; } ;
struct utrace {int /*<<< orphan*/ * reporting; } ;
struct task_struct {int dummy; } ;

/* Variables and functions */
 int UTRACE_RESUME_MASK ; 
 int /*<<< orphan*/  finish_callback_report (struct task_struct*,struct utrace*,struct utrace_report*,struct utrace_engine*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  might_sleep () ; 
 int /*<<< orphan*/  utrace_detached_ops ; 
 int /*<<< orphan*/  utrace_resume_action (int) ; 

__attribute__((used)) static bool finish_callback(struct task_struct *task, struct utrace *utrace,
			    struct utrace_report *report,
			    struct utrace_engine *engine,
			    u32 ret)
{
	report->result = ret & ~UTRACE_RESUME_MASK;
	finish_callback_report(task, utrace, report, engine,
			       utrace_resume_action(ret));

	/*
	 * Now that we have applied the effect of the return value,
	 * clear this so that utrace_barrier() can stop waiting.
	 * A subsequent utrace_control() can stop or resume @engine
	 * and know this was ordered after its callback's action.
	 *
	 * We don't need any barriers here because utrace_barrier()
	 * takes utrace->lock.  If we touched engine->flags above,
	 * the lock guaranteed this change was before utrace_barrier()
	 * examined utrace->reporting.
	 */
	utrace->reporting = NULL;

	/*
	 * We've just done an engine callback.  These are allowed to sleep,
	 * though all well-behaved ones restrict that to blocking kalloc()
	 * or quickly-acquired mutex_lock() and the like.  This is a good
	 * place to make sure tracing engines don't introduce too much
	 * latency under voluntary preemption.
	 */
	might_sleep();

	return engine->ops == &utrace_detached_ops;
}