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
struct task_struct {TYPE_1__ thread; } ;

/* Variables and functions */
 unsigned int PT_MAX ; 
 unsigned int PT_USP ; 
 scalar_t__ task_pt_regs (struct task_struct*) ; 

inline int put_reg(struct task_struct *task, unsigned int regno,
			  unsigned long data)
{
	if (regno == PT_USP)
		task->thread.usp = data;
	else if (regno < PT_MAX)
		((unsigned long *)task_pt_regs(task))[regno] = data;
	else
		return -1;
	return 0;
}