#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct thread_info {int dummy; } ;
struct task_struct {int dummy; } ;

/* Variables and functions */
 scalar_t__ KSTK_EBP (struct task_struct*) ; 
 int THREAD_SIZE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct task_struct* current ; 
 int /*<<< orphan*/  print_context_stack (struct thread_info*,unsigned long*,unsigned long) ; 
 int /*<<< orphan*/  printk (char*) ; 

void show_trace(struct task_struct* task, unsigned long * stack)
{
	unsigned long ebp;
	struct thread_info *context;

	/* Turn this into BUG_ON if possible. */
	if (!stack) {
		stack = (unsigned long*) &stack;
		printk("show_trace: got NULL stack, implicit assumption task == current");
		WARN_ON(1);
	}

	if (!task)
		task = current;

	if (task != current) {
		ebp = (unsigned long) KSTK_EBP(task);
	} else {
		asm ("movl %%ebp, %0" : "=r" (ebp) : );
	}

	context = (struct thread_info *)
		((unsigned long)stack & (~(THREAD_SIZE - 1)));
	print_context_stack(context, stack, ebp);

	printk("\n");
}