#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct uml_pt_regs {int dummy; } ;
struct TYPE_4__ {int ptrace; scalar_t__ exit_code; int /*<<< orphan*/  audit_context; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDITSC_RESULT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HOST_AUDIT_ARCH ; 
 int PT_DTRACE ; 
 int PT_PTRACED ; 
 int PT_TRACESYSGOOD ; 
 int SIGTRAP ; 
 int /*<<< orphan*/  TIF_SIGPENDING ; 
 int /*<<< orphan*/  TIF_SYSCALL_TRACE ; 
 int /*<<< orphan*/  UPT_SYSCALL_ARG1 (struct uml_pt_regs*) ; 
 int /*<<< orphan*/  UPT_SYSCALL_ARG2 (struct uml_pt_regs*) ; 
 int /*<<< orphan*/  UPT_SYSCALL_ARG3 (struct uml_pt_regs*) ; 
 int /*<<< orphan*/  UPT_SYSCALL_ARG4 (struct uml_pt_regs*) ; 
 int /*<<< orphan*/  UPT_SYSCALL_NR (struct uml_pt_regs*) ; 
 int /*<<< orphan*/  UPT_SYSCALL_RET (struct uml_pt_regs*) ; 
 int /*<<< orphan*/  audit_syscall_entry (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  audit_syscall_exit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  ptrace_notify (int) ; 
 int /*<<< orphan*/  send_sig (scalar_t__,TYPE_1__*,int) ; 
 int /*<<< orphan*/  send_sigtrap (TYPE_1__*,struct uml_pt_regs*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_thread_flag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_thread_flag (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

void syscall_trace(struct uml_pt_regs *regs, int entryexit)
{
	int is_singlestep = (current->ptrace & PT_DTRACE) && entryexit;
	int tracesysgood;

	if (unlikely(current->audit_context)) {
		if (!entryexit)
			audit_syscall_entry(HOST_AUDIT_ARCH,
					    UPT_SYSCALL_NR(regs),
					    UPT_SYSCALL_ARG1(regs),
					    UPT_SYSCALL_ARG2(regs),
					    UPT_SYSCALL_ARG3(regs),
					    UPT_SYSCALL_ARG4(regs));
		else audit_syscall_exit(AUDITSC_RESULT(UPT_SYSCALL_RET(regs)),
					UPT_SYSCALL_RET(regs));
	}

	/* Fake a debug trap */
	if (is_singlestep)
		send_sigtrap(current, regs, 0);

	if (!test_thread_flag(TIF_SYSCALL_TRACE))
		return;

	if (!(current->ptrace & PT_PTRACED))
		return;

	/*
	 * the 0x80 provides a way for the tracing parent to distinguish
	 * between a syscall stop and SIGTRAP delivery
	 */
	tracesysgood = (current->ptrace & PT_TRACESYSGOOD);
	ptrace_notify(SIGTRAP | (tracesysgood ? 0x80 : 0));

	if (entryexit) /* force do_signal() --> is_syscall() */
		set_thread_flag(TIF_SIGPENDING);

	/*
	 * this isn't the same as continuing with a signal, but it will do
	 * for normal use.  strace only continues with a signal if the
	 * stopping signal is not SIGTRAP.  -brl
	 */
	if (current->exit_code) {
		send_sig(current->exit_code, current, 1);
		current->exit_code = 0;
	}
}