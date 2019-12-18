#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {unsigned long usp; unsigned long ksp; } ;
struct task_struct {TYPE_1__ thread; scalar_t__ mm; int /*<<< orphan*/ * clear_child_tid; int /*<<< orphan*/  set_child_tid; } ;
struct switch_stack {unsigned long return_ip; scalar_t__ r9; } ;
struct pt_regs {int /*<<< orphan*/  mof; scalar_t__ r10; } ;
struct TYPE_4__ {int /*<<< orphan*/  tls; } ;

/* Variables and functions */
 unsigned long CLONE_SETTLS ; 
 scalar_t__ ret_from_fork ; 
 struct pt_regs* task_pt_regs (struct task_struct*) ; 
 TYPE_2__* task_thread_info (struct task_struct*) ; 

int
copy_thread(unsigned long clone_flags, unsigned long usp,
	unsigned long unused,
	struct task_struct *p, struct pt_regs *regs)
{
	struct pt_regs *childregs;
	struct switch_stack *swstack;

	/*
	 * Put the pt_regs structure at the end of the new kernel stack page and
	 * fix it up. Note: the task_struct doubles as the kernel stack for the
	 * task.
	 */
	childregs = task_pt_regs(p);
	*childregs = *regs;	/* Struct copy of pt_regs. */
        p->set_child_tid = p->clear_child_tid = NULL;
        childregs->r10 = 0;	/* Child returns 0 after a fork/clone. */

	/* Set a new TLS ?
	 * The TLS is in $mof beacuse it is the 5th argument to sys_clone.
	 */
	if (p->mm && (clone_flags & CLONE_SETTLS)) {
		task_thread_info(p)->tls = regs->mof;
	}

	/* Put the switch stack right below the pt_regs. */
	swstack = ((struct switch_stack *) childregs) - 1;

	/* Parameter to ret_from_sys_call. 0 is don't restart the syscall. */
	swstack->r9 = 0;

	/*
	 * We want to return into ret_from_sys_call after the _resume.
	 * ret_from_fork will call ret_from_sys_call.
	 */
	swstack->return_ip = (unsigned long) ret_from_fork;

	/* Fix the user-mode and kernel-mode stackpointer. */
	p->thread.usp = usp;
	p->thread.ksp = (unsigned long) swstack;

	return 0;
}