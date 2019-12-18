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
struct TYPE_2__ {unsigned long fp; struct pt_regs* frame0; } ;
struct task_struct {scalar_t__ state; TYPE_1__ thread; } ;
struct pt_regs {int dummy; } ;

/* Variables and functions */
 scalar_t__ TASK_RUNNING ; 
 struct task_struct* current ; 
 int /*<<< orphan*/  in_sched_functions (unsigned long) ; 

unsigned long get_wchan(struct task_struct *p)
{
	struct pt_regs *regs0;
	unsigned long fp, pc;
	unsigned long stack_limit;
	int count = 0;
	if (!p || p == current || p->state == TASK_RUNNING)
		return 0;

	stack_limit = (unsigned long) (p + 1);
	fp = p->thread.fp;
	regs0 = p->thread.frame0;

	do {
		if (fp < stack_limit || fp >= (unsigned long) regs0 || fp & 3)
			return 0;

		pc = ((unsigned long *) fp)[2];

		/* FIXME: This depends on the order of these functions. */
		if (!in_sched_functions(pc))
			return pc;

		fp = *(unsigned long *) fp;
	} while (count++ < 16);

	return 0;
}