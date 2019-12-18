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
struct task_struct {int dummy; } ;
struct pt_regs {int dummy; } ;

/* Variables and functions */
 struct task_struct* current ; 
 int /*<<< orphan*/  debug_show_held_locks (struct task_struct*) ; 
 int /*<<< orphan*/  print_trace_ops ; 
 int /*<<< orphan*/  printk (char*) ; 
 int /*<<< orphan*/  unwind_stack (struct task_struct*,struct pt_regs*,unsigned long*,int /*<<< orphan*/ *,char*) ; 
 scalar_t__ user_mode (struct pt_regs*) ; 

void show_trace(struct task_struct *tsk, unsigned long *sp,
		struct pt_regs *regs)
{
	if (regs && user_mode(regs))
		return;

	printk("\nCall trace:\n");

	unwind_stack(tsk, regs, sp, &print_trace_ops, "");

	printk("\n");

	if (!tsk)
		tsk = current;

	debug_show_held_locks(tsk);
}