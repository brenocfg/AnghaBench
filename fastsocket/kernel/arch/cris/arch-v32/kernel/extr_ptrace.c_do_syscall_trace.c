#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int ptrace; scalar_t__ exit_code; } ;

/* Variables and functions */
 int PT_PTRACED ; 
 int PT_TRACESYSGOOD ; 
 int SIGTRAP ; 
 int /*<<< orphan*/  TIF_SYSCALL_TRACE ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  ptrace_notify (int) ; 
 int /*<<< orphan*/  send_sig (scalar_t__,TYPE_1__*,int) ; 
 int /*<<< orphan*/  test_thread_flag (int /*<<< orphan*/ ) ; 

void do_syscall_trace(void)
{
	if (!test_thread_flag(TIF_SYSCALL_TRACE))
		return;

	if (!(current->ptrace & PT_PTRACED))
		return;

	/* the 0x80 provides a way for the tracing parent to distinguish
	   between a syscall stop and SIGTRAP delivery */
	ptrace_notify(SIGTRAP | ((current->ptrace & PT_TRACESYSGOOD)
				 ? 0x80 : 0));

	/*
	 * This isn't the same as continuing with a signal, but it will do for
	 * normal use.
	 */
	if (current->exit_code) {
		send_sig(current->exit_code, current, 1);
		current->exit_code = 0;
	}
}