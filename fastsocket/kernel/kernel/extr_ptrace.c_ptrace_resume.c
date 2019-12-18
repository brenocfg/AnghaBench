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
struct task_struct {long exit_code; } ;

/* Variables and functions */
 int EIO ; 
 long PTRACE_SYSCALL ; 
 long PTRACE_SYSEMU ; 
 long PTRACE_SYSEMU_SINGLESTEP ; 
 int /*<<< orphan*/  TIF_SYSCALL_EMU ; 
 int /*<<< orphan*/  TIF_SYSCALL_TRACE ; 
 int /*<<< orphan*/  arch_has_block_step () ; 
 int /*<<< orphan*/  arch_has_single_step () ; 
 int /*<<< orphan*/  clear_tsk_thread_flag (struct task_struct*,int /*<<< orphan*/ ) ; 
 scalar_t__ is_singleblock (long) ; 
 scalar_t__ is_singlestep (long) ; 
 scalar_t__ is_sysemu_singlestep (long) ; 
 int /*<<< orphan*/  set_tsk_thread_flag (struct task_struct*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  user_disable_single_step (struct task_struct*) ; 
 int /*<<< orphan*/  user_enable_block_step (struct task_struct*) ; 
 int /*<<< orphan*/  user_enable_single_step (struct task_struct*) ; 
 int /*<<< orphan*/  valid_signal (long) ; 
 int /*<<< orphan*/  wake_up_process (struct task_struct*) ; 

__attribute__((used)) static int ptrace_resume(struct task_struct *child, long request, long data)
{
	if (!valid_signal(data))
		return -EIO;

	if (request == PTRACE_SYSCALL)
		set_tsk_thread_flag(child, TIF_SYSCALL_TRACE);
	else
		clear_tsk_thread_flag(child, TIF_SYSCALL_TRACE);

#ifdef TIF_SYSCALL_EMU
	if (request == PTRACE_SYSEMU || request == PTRACE_SYSEMU_SINGLESTEP)
		set_tsk_thread_flag(child, TIF_SYSCALL_EMU);
	else
		clear_tsk_thread_flag(child, TIF_SYSCALL_EMU);
#endif

	if (is_singleblock(request)) {
		if (unlikely(!arch_has_block_step()))
			return -EIO;
		user_enable_block_step(child);
	} else if (is_singlestep(request) || is_sysemu_singlestep(request)) {
		if (unlikely(!arch_has_single_step()))
			return -EIO;
		user_enable_single_step(child);
	} else {
		user_disable_single_step(child);
	}

	child->exit_code = data;
	wake_up_process(child);

	return 0;
}