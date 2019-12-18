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
struct TYPE_2__ {int /*<<< orphan*/ * regs; } ;
struct task_struct {TYPE_1__ thread; } ;
struct pt_regs {int dummy; } ;

/* Variables and functions */
 unsigned long EIO ; 
 int PT_MSR ; 
 unsigned long get_user_msr (struct task_struct*) ; 

unsigned long ptrace_get_reg(struct task_struct *task, int regno)
{
	if (task->thread.regs == NULL)
		return -EIO;

	if (regno == PT_MSR)
		return get_user_msr(task);

	if (regno < (sizeof(struct pt_regs) / sizeof(unsigned long)))
		return ((unsigned long *)task->thread.regs)[regno];

	return -EIO;
}