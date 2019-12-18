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
struct pt_regs {int dummy; } ;
struct TYPE_2__ {int ptrace; } ;

/* Variables and functions */
 int PT_PTRACED ; 
 int /*<<< orphan*/  TIF_SYSCALL_TRACE ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  do_syscall_trace () ; 
 scalar_t__ test_thread_flag (int /*<<< orphan*/ ) ; 

void do_syscall_trace_leave(struct pt_regs *regs)
{
	if ((test_thread_flag(TIF_SYSCALL_TRACE))
			&& (current->ptrace & PT_PTRACED))
		do_syscall_trace();
}