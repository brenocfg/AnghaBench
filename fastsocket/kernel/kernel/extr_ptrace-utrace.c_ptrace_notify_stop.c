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
struct task_struct {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct utrace_engine*) ; 
 int /*<<< orphan*/  do_ptrace_notify_stop (int /*<<< orphan*/ ,struct task_struct*) ; 
 int /*<<< orphan*/  ptrace_context (struct utrace_engine*) ; 
 struct utrace_engine* ptrace_lookup_engine (struct task_struct*) ; 
 int /*<<< orphan*/  utrace_engine_put (struct utrace_engine*) ; 

void ptrace_notify_stop(struct task_struct *tracee)
{
	struct utrace_engine *engine = ptrace_lookup_engine(tracee);

	if (IS_ERR(engine))
		return;

	do_ptrace_notify_stop(ptrace_context(engine), tracee);
	utrace_engine_put(engine);
}