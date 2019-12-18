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
struct utrace_engine {int dummy; } ;
struct task_struct {int /*<<< orphan*/  exit_state; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct utrace_engine*) ; 
 int PTR_ERR (struct utrace_engine*) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct utrace_engine* ptrace_attach_engine (struct task_struct*) ; 
 int ptrace_set_events (struct task_struct*,struct utrace_engine*,int) ; 
 int /*<<< orphan*/  utrace_engine_put (struct utrace_engine*) ; 

__attribute__((used)) static int ptrace_attach_task(struct task_struct *tracee, int options)
{
	struct utrace_engine *engine;
	int err;

	engine = ptrace_attach_engine(tracee);
	if (IS_ERR(engine))
		return PTR_ERR(engine);
	/*
	 * It can fail only if the tracee is dead, the caller
	 * must notice this before setting PT_UTRACED.
	 */
	err = ptrace_set_events(tracee, engine, options);
	WARN_ON(err && !tracee->exit_state);
	utrace_engine_put(engine);
	return 0;
}