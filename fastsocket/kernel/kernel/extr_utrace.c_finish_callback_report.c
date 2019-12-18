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
struct utrace_report {int detaches; int action; int resume_action; } ;
struct utrace_engine {int /*<<< orphan*/ * ops; } ;
struct utrace {int /*<<< orphan*/  lock; } ;
struct task_struct {int dummy; } ;
typedef  enum utrace_resume_action { ____Placeholder_utrace_resume_action } utrace_resume_action ;

/* Variables and functions */
 int UTRACE_DETACH ; 
 int UTRACE_STOP ; 
 int /*<<< orphan*/  clear_engine_wants_stop (struct utrace_engine*) ; 
 scalar_t__ engine_wants_stop (struct utrace_engine*) ; 
 int /*<<< orphan*/  mark_engine_wants_stop (struct task_struct*,struct utrace_engine*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  utrace_detached_ops ; 

__attribute__((used)) static void finish_callback_report(struct task_struct *task,
				   struct utrace *utrace,
				   struct utrace_report *report,
				   struct utrace_engine *engine,
				   enum utrace_resume_action action)
{
	if (action == UTRACE_DETACH) {
		/*
		 * By holding the lock here, we make sure that
		 * utrace_barrier() (really get_utrace_lock()) sees the
		 * effect of this detach.  Otherwise utrace_barrier() could
		 * return 0 after this callback had returned UTRACE_DETACH.
		 * This way, a 0 return is an unambiguous indicator that any
		 * callback returning UTRACE_DETACH has indeed caused detach.
		 */
		spin_lock(&utrace->lock);
		engine->ops = &utrace_detached_ops;
		spin_unlock(&utrace->lock);
	}

	/*
	 * If utrace_control() was used, treat that like UTRACE_DETACH here.
	 */
	if (engine->ops == &utrace_detached_ops) {
		report->detaches = true;
		return;
	}

	if (action < report->action)
		report->action = action;

	if (action != UTRACE_STOP) {
		if (action < report->resume_action)
			report->resume_action = action;

		if (engine_wants_stop(engine)) {
			spin_lock(&utrace->lock);
			clear_engine_wants_stop(engine);
			spin_unlock(&utrace->lock);
		}

		return;
	}

	if (!engine_wants_stop(engine)) {
		spin_lock(&utrace->lock);
		/*
		 * If utrace_control() came in and detached us
		 * before we got the lock, we must not stop now.
		 */
		if (unlikely(engine->ops == &utrace_detached_ops))
			report->detaches = true;
		else
			mark_engine_wants_stop(task, engine);
		spin_unlock(&utrace->lock);
	}
}