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
struct TYPE_2__ {scalar_t__ sp; } ;
struct task_struct {TYPE_1__ thread; } ;

/* Variables and functions */
 int kstack_depth_to_print ; 
 scalar_t__ kstack_end (unsigned long*) ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 int /*<<< orphan*/  show_trace (struct task_struct*,unsigned long*) ; 

void show_stack(struct task_struct *task, unsigned long *sp)
{
	unsigned long  *stack;
	int  i;

	/*
	 * debugging aid: "show_stack(NULL);" prints the
	 * back trace for this cpu.
	 */

	if(sp==NULL) {
		if (task)
			sp = (unsigned long *)task->thread.sp;
		else
			sp=(unsigned long*)&sp;
	}

	stack = sp;
	for(i=0; i < kstack_depth_to_print; i++) {
		if (kstack_end(stack))
			break;
		if (i && ((i % 4) == 0))
			printk("\n       ");
		printk("%08lx ", *stack++);
	}
	printk("\n");
	show_trace(task, sp);
}