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
struct utrace_report {int spurious; int /*<<< orphan*/  action; } ;
struct utrace_engine_ops {int /*<<< orphan*/  (* report_quiesce ) (int /*<<< orphan*/ ,struct utrace_engine*,unsigned long) ;} ;
struct utrace_engine {unsigned long flags; struct utrace_engine_ops* ops; } ;
struct utrace {struct utrace_engine* reporting; } ;
struct task_struct {int dummy; } ;

/* Variables and functions */
 unsigned long ENGINE_STOP ; 
 int /*<<< orphan*/  QUIESCE ; 
 unsigned long UTRACE_EVENT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UTRACE_STOP ; 
 scalar_t__ finish_callback (struct task_struct*,struct utrace*,struct utrace_report*,struct utrace_engine*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_mb () ; 
 int /*<<< orphan*/  smp_rmb () ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct utrace_engine*,unsigned long) ; 

__attribute__((used)) static const struct utrace_engine_ops *start_callback(
	struct utrace *utrace, struct utrace_report *report,
	struct utrace_engine *engine, struct task_struct *task,
	unsigned long event)
{
	const struct utrace_engine_ops *ops;
	unsigned long want;

	/*
	 * This barrier ensures that we've set utrace->reporting before
	 * we examine engine->flags or engine->ops.  utrace_barrier()
	 * relies on this ordering to indicate that the effect of any
	 * utrace_control() and utrace_set_events() calls is in place
	 * by the time utrace->reporting can be seen to be NULL.
	 */
	utrace->reporting = engine;
	smp_mb();

	/*
	 * This pairs with the barrier in mark_engine_detached().
	 * It makes sure that we never see the old ops vector with
	 * the new flags, in case the original vector had no report_quiesce.
	 */
	want = engine->flags;
	smp_rmb();
	ops = engine->ops;

	if (want & UTRACE_EVENT(QUIESCE)) {
		if (finish_callback(task, utrace, report, engine,
				    (*ops->report_quiesce)(report->action,
							   engine, event)))
			return NULL;

		/*
		 * finish_callback() reset utrace->reporting after the
		 * quiesce callback.  Now we set it again (as above)
		 * before re-examining engine->flags, which could have
		 * been changed synchronously by ->report_quiesce or
		 * asynchronously by utrace_control() or utrace_set_events().
		 */
		utrace->reporting = engine;
		smp_mb();
		want = engine->flags;
	}

	if (want & ENGINE_STOP)
		report->action = UTRACE_STOP;

	if (want & event) {
		report->spurious = false;
		return ops;
	}

	utrace->reporting = NULL;
	return NULL;
}