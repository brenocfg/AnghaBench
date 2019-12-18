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
struct pt_regs {long* gr; } ;

/* Variables and functions */
 int /*<<< orphan*/  TIF_SYSCALL_TRACE ; 
 scalar_t__ test_thread_flag (int /*<<< orphan*/ ) ; 
 scalar_t__ tracehook_report_syscall_entry (struct pt_regs*) ; 

long do_syscall_trace_enter(struct pt_regs *regs)
{
	if (test_thread_flag(TIF_SYSCALL_TRACE) &&
	    tracehook_report_syscall_entry(regs))
		return -1L;

	return regs->gr[20];
}