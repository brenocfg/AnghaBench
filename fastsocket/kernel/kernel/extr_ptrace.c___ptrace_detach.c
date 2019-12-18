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
struct task_struct {scalar_t__ exit_state; int exit_signal; int /*<<< orphan*/  sighand; int /*<<< orphan*/  real_parent; } ;

/* Variables and functions */
 scalar_t__ EXIT_DEAD ; 
 scalar_t__ EXIT_ZOMBIE ; 
 int /*<<< orphan*/  __ptrace_unlink (struct task_struct*) ; 
 int /*<<< orphan*/  __wake_up_parent (struct task_struct*,struct task_struct*) ; 
 int /*<<< orphan*/  do_notify_parent (struct task_struct*,int) ; 
 scalar_t__ ignoring_children (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  same_thread_group (int /*<<< orphan*/ ,struct task_struct*) ; 
 scalar_t__ task_detached (struct task_struct*) ; 
 scalar_t__ thread_group_empty (struct task_struct*) ; 

bool __ptrace_detach(struct task_struct *tracer, struct task_struct *p)
{
	__ptrace_unlink(p);

	if (p->exit_state == EXIT_ZOMBIE) {
		if (!task_detached(p) && thread_group_empty(p)) {
			if (!same_thread_group(p->real_parent, tracer))
				do_notify_parent(p, p->exit_signal);
			else if (ignoring_children(tracer->sighand)) {
				__wake_up_parent(p, tracer);
				p->exit_signal = -1;
			}
		}
		if (task_detached(p)) {
			/* Mark it as in the process of being reaped. */
			p->exit_state = EXIT_DEAD;
			return true;
		}
	}

	return false;
}