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
struct thread_info {int dummy; } ;
struct TYPE_2__ {unsigned long reg0; unsigned long reg3; scalar_t__ cp0_psr; } ;
struct task_struct {unsigned long pid; TYPE_1__ thread; int /*<<< orphan*/ * clear_child_tid; int /*<<< orphan*/ * set_child_tid; } ;
struct pt_regs {unsigned long* regs; int cp0_psr; } ;

/* Variables and functions */
 scalar_t__ ret_from_fork ; 
 struct pt_regs* task_pt_regs (struct task_struct*) ; 
 struct thread_info* task_thread_info (struct task_struct*) ; 

int copy_thread(unsigned long clone_flags, unsigned long usp,
		unsigned long unused,
		struct task_struct *p, struct pt_regs *regs)
{
	struct thread_info *ti = task_thread_info(p);
	struct pt_regs *childregs = task_pt_regs(p);

	p->set_child_tid = NULL;
	p->clear_child_tid = NULL;

	*childregs = *regs;
	childregs->regs[7] = 0;		/* Clear error flag */
	childregs->regs[4] = 0;		/* Child gets zero as return value */
	regs->regs[4] = p->pid;

	if (childregs->cp0_psr & 0x8) {	/* test kernel fork or user fork */
		childregs->regs[0] = usp;		/* user fork */
	} else {
		childregs->regs[28] = (unsigned long) ti; /* kernel fork */
		childregs->regs[0] = (unsigned long) childregs;
	}

	p->thread.reg0 = (unsigned long) childregs;
	p->thread.reg3 = (unsigned long) ret_from_fork;
	p->thread.cp0_psr = 0;

	return 0;
}