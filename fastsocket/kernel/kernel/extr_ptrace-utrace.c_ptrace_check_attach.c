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
struct utrace_examiner {int dummy; } ;
struct utrace_engine {int dummy; } ;
struct task_struct {scalar_t__ parent; } ;

/* Variables and functions */
 int ESRCH ; 
 scalar_t__ IS_ERR (struct utrace_engine*) ; 
 int /*<<< orphan*/  UTRACE_STOP ; 
 scalar_t__ current ; 
 struct utrace_engine* ptrace_lookup_engine (struct task_struct*) ; 
 int /*<<< orphan*/  task_is_stopped_or_traced (struct task_struct*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  utrace_control (struct task_struct*,struct utrace_engine*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  utrace_engine_put (struct utrace_engine*) ; 
 int /*<<< orphan*/  utrace_freeze_stop (struct task_struct*) ; 
 int /*<<< orphan*/  utrace_prepare_examine (struct task_struct*,struct utrace_engine*,struct utrace_examiner*) ; 
 int /*<<< orphan*/  utrace_unfreeze_stop (struct task_struct*) ; 

int ptrace_check_attach(struct task_struct *child, int kill)
{
	struct utrace_engine *engine;
	struct utrace_examiner exam;
	int ret = -ESRCH;

	engine = ptrace_lookup_engine(child);
	if (IS_ERR(engine))
		return ret;

	if (child->parent != current)
		goto out;

	if (unlikely(kill))
		ret = 0;

	if (!task_is_stopped_or_traced(child))
		goto out;
	/*
	 * Make sure our engine has already stopped the child.
	 * Then wait for it to be off the CPU.
	 */
	utrace_freeze_stop(child);
	if (!utrace_control(child, engine, UTRACE_STOP) &&
	    !utrace_prepare_examine(child, engine, &exam))
		ret = 0;
	else
		utrace_unfreeze_stop(child);

out:
	utrace_engine_put(engine);
	return ret;
}