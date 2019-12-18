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

/* Variables and functions */
 unsigned long DEBUGCTLMSR_BTF ; 
 int /*<<< orphan*/  TIF_BLOCKSTEP ; 
 int /*<<< orphan*/  clear_tsk_thread_flag (struct task_struct*,int /*<<< orphan*/ ) ; 
 scalar_t__ enable_single_step (struct task_struct*) ; 
 unsigned long get_debugctlmsr () ; 
 int /*<<< orphan*/  set_tsk_thread_flag (struct task_struct*,int /*<<< orphan*/ ) ; 
 scalar_t__ test_tsk_thread_flag (struct task_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_debugctlmsr (unsigned long) ; 

__attribute__((used)) static void enable_step(struct task_struct *child, bool block)
{
	/*
	 * Make sure block stepping (BTF) is not enabled unless it should be.
	 * Note that we don't try to worry about any is_setting_trap_flag()
	 * instructions after the first when using block stepping.
	 * So noone should try to use debugger block stepping in a program
	 * that uses user-mode single stepping itself.
	 */
	if (enable_single_step(child) && block) {
		unsigned long debugctl = get_debugctlmsr();

		debugctl |= DEBUGCTLMSR_BTF;
		update_debugctlmsr(debugctl);
		set_tsk_thread_flag(child, TIF_BLOCKSTEP);
	} else if (test_tsk_thread_flag(child, TIF_BLOCKSTEP)) {
		unsigned long debugctl = get_debugctlmsr();

		debugctl &= ~DEBUGCTLMSR_BTF;
		update_debugctlmsr(debugctl);
		clear_tsk_thread_flag(child, TIF_BLOCKSTEP);
	}
}