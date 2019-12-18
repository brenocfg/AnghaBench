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
struct TYPE_2__ {scalar_t__ ksp; } ;
struct task_struct {TYPE_1__ thread; } ;

/* Variables and functions */
 int THREAD_SIZE ; 
 scalar_t__ __get_user (unsigned long,unsigned long*) ; 
 int kstack_depth_to_print ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 scalar_t__ rdsp () ; 
 int /*<<< orphan*/  show_trace (unsigned long*) ; 

void
show_stack(struct task_struct *task, unsigned long *sp)
{
	unsigned long *stack, addr;
	int i;

	/*
	 * debugging aid: "show_stack(NULL);" prints a
	 * back trace.
	 */

	if (sp == NULL) {
		if (task)
			sp = (unsigned long*)task->thread.ksp;
		else
			sp = (unsigned long*)rdsp();
	}

	stack = sp;

	printk("\nStack from %08lx:\n       ", (unsigned long)stack);
	for (i = 0; i < kstack_depth_to_print; i++) {
		if (((long)stack & (THREAD_SIZE-1)) == 0)
			break;
		if (i && ((i % 8) == 0))
			printk("\n       ");
		if (__get_user(addr, stack)) {
			/* This message matches "failing address" marked
			   s390 in ksymoops, so lines containing it will
			   not be filtered out by ksymoops.  */
			printk("Failing address 0x%lx\n", (unsigned long)stack);
			break;
		}
		stack++;
		printk("%08lx ", addr);
	}
	show_trace(sp);
}