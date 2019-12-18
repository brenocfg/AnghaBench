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
struct TYPE_2__ {unsigned long usp; } ;
struct task_struct {int /*<<< orphan*/  pid; TYPE_1__ thread; } ;

/* Variables and functions */
 unsigned int PT_EDA ; 
 unsigned int PT_MAX ; 
 unsigned int PT_PPC ; 
 unsigned int PT_USP ; 
 unsigned long get_debugreg (int /*<<< orphan*/ ,unsigned int) ; 
 unsigned long get_pseudo_pc (struct task_struct*) ; 
 scalar_t__ task_pt_regs (struct task_struct*) ; 

long get_reg(struct task_struct *task, unsigned int regno)
{
	/* USP is a special case, it's not in the pt_regs struct but
	 * in the tasks thread struct
	 */
	unsigned long ret;

	if (regno <= PT_EDA)
		ret = ((unsigned long *)task_pt_regs(task))[regno];
	else if (regno == PT_USP)
		ret = task->thread.usp;
	else if (regno == PT_PPC)
		ret = get_pseudo_pc(task);
	else if (regno <= PT_MAX)
		ret = get_debugreg(task->pid, regno);
	else
		ret = 0;

	return ret;
}