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
struct pt_regs {unsigned long flags; } ;

/* Variables and functions */
 unsigned long FLAG_MASK ; 
 int /*<<< orphan*/  TIF_FORCED_TF ; 
 unsigned long X86_EFLAGS_TF ; 
 int /*<<< orphan*/  clear_tsk_thread_flag (struct task_struct*,int /*<<< orphan*/ ) ; 
 struct pt_regs* task_pt_regs (struct task_struct*) ; 
 scalar_t__ test_tsk_thread_flag (struct task_struct*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int set_flags(struct task_struct *task, unsigned long value)
{
	struct pt_regs *regs = task_pt_regs(task);

	/*
	 * If the user value contains TF, mark that
	 * it was not "us" (the debugger) that set it.
	 * If not, make sure it stays set if we had.
	 */
	if (value & X86_EFLAGS_TF)
		clear_tsk_thread_flag(task, TIF_FORCED_TF);
	else if (test_tsk_thread_flag(task, TIF_FORCED_TF))
		value |= X86_EFLAGS_TF;

	regs->flags = (regs->flags & ~FLAG_MASK) | (value & FLAG_MASK);

	return 0;
}