#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_5__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int flags; } ;
struct TYPE_6__ {TYPE_5__* real_parent; int /*<<< orphan*/  ptrace; int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int EPERM ; 
 int PF_EXITING ; 
 int /*<<< orphan*/  PT_UTRACED ; 
 int /*<<< orphan*/  __ptrace_link (TYPE_1__*,TYPE_5__*) ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  ptrace_abort_attach (TYPE_1__*) ; 
 int ptrace_attach_task (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int security_ptrace_traceme (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tasklist_lock ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  write_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_irq (int /*<<< orphan*/ *) ; 

int ptrace_traceme(void)
{
	bool detach = true;
	int ret = ptrace_attach_task(current, 0);

	if (unlikely(ret))
		return ret;

	ret = -EPERM;
	write_lock_irq(&tasklist_lock);
	BUG_ON(current->ptrace);
	ret = security_ptrace_traceme(current->parent);
	/*
	 * Check PF_EXITING to ensure ->real_parent has not passed
	 * exit_ptrace(). Otherwise we don't report the error but
	 * pretend ->real_parent untraces us right after return.
	 */
	if (!ret && !(current->real_parent->flags & PF_EXITING)) {
		current->ptrace = PT_UTRACED;
		__ptrace_link(current, current->real_parent);
		detach = false;
	}
	write_unlock_irq(&tasklist_lock);

	if (detach)
		ptrace_abort_attach(current);
	return ret;
}