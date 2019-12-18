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
struct TYPE_2__ {unsigned long sp; unsigned long lr; } ;
struct task_struct {TYPE_1__ thread; scalar_t__ pid; } ;
struct pt_regs {unsigned long spu; scalar_t__ r0; } ;

/* Variables and functions */
 struct pt_regs* task_pt_regs (struct task_struct*) ; 

int copy_thread(unsigned long clone_flags, unsigned long spu,
	unsigned long unused, struct task_struct *tsk, struct pt_regs *regs)
{
	struct pt_regs *childregs = task_pt_regs(tsk);
	extern void ret_from_fork(void);

	/* Copy registers */
	*childregs = *regs;

	childregs->spu = spu;
	childregs->r0 = 0;	/* Child gets zero as return value */
	regs->r0 = tsk->pid;
	tsk->thread.sp = (unsigned long)childregs;
	tsk->thread.lr = (unsigned long)ret_from_fork;

	return 0;
}