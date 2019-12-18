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

/* Variables and functions */
 int /*<<< orphan*/  PTRACE_TRACEME ; 
 int /*<<< orphan*/  SIGKILL ; 
 int /*<<< orphan*/  SIGSTOP ; 
 int /*<<< orphan*/  SIGWINCH ; 
 scalar_t__ change_sig (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit (int) ; 
 int getppid () ; 
 int /*<<< orphan*/  kill (int,int /*<<< orphan*/ ) ; 
 int os_getpid () ; 
 int /*<<< orphan*/  perror (char*) ; 
 scalar_t__ ptrace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ptrace_child(void)
{
	int ret;
	/* Calling os_getpid because some libcs cached getpid incorrectly */
	int pid = os_getpid(), ppid = getppid();
	int sc_result;

	if (change_sig(SIGWINCH, 0) < 0 ||
	    ptrace(PTRACE_TRACEME, 0, 0, 0) < 0) {
		perror("ptrace");
		kill(pid, SIGKILL);
	}
	kill(pid, SIGSTOP);

	/*
	 * This syscall will be intercepted by the parent. Don't call more than
	 * once, please.
	 */
	sc_result = os_getpid();

	if (sc_result == pid)
		/* Nothing modified by the parent, we are running normally. */
		ret = 1;
	else if (sc_result == ppid)
		/*
		 * Expected in check_ptrace and check_sysemu when they succeed
		 * in modifying the stack frame
		 */
		ret = 0;
	else
		/* Serious trouble! This could be caused by a bug in host 2.6
		 * SKAS3/2.6 patch before release -V6, together with a bug in
		 * the UML code itself.
		 */
		ret = 2;

	exit(ret);
}