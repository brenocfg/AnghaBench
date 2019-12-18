#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  signal; } ;
struct task_struct {int flags; TYPE_1__ pending; scalar_t__ ptrace; struct task_struct* parent; } ;

/* Variables and functions */
 int PF_EXITING ; 
 int /*<<< orphan*/  SIGSTOP ; 
 int /*<<< orphan*/  TIF_SIGPENDING ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  __ptrace_link (struct task_struct*,struct task_struct*) ; 
 struct task_struct* current ; 
 int /*<<< orphan*/  ptrace_abort_attach (struct task_struct*) ; 
 int ptrace_attach_task (struct task_struct*,int) ; 
 int /*<<< orphan*/  set_tsk_thread_flag (struct task_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigaddset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tasklist_lock ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  write_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ptrace_clone_attach(struct task_struct *child,
				int options)
{
	struct task_struct *parent = current;
	struct task_struct *tracer;
	bool abort = true;

	if (unlikely(ptrace_attach_task(child, options))) {
		WARN_ON(1);
		return;
	}

	write_lock_irq(&tasklist_lock);
	tracer = parent->parent;
	if (!(tracer->flags & PF_EXITING) && parent->ptrace) {
		child->ptrace = parent->ptrace;
		__ptrace_link(child, tracer);
		abort = false;
	}
	write_unlock_irq(&tasklist_lock);
	if (unlikely(abort)) {
		ptrace_abort_attach(child);
		return;
	}

	sigaddset(&child->pending.signal, SIGSTOP);
	set_tsk_thread_flag(child, TIF_SIGPENDING);
}