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
 int /*<<< orphan*/  CATCH_EINTR (int) ; 
 scalar_t__ SIGSTOP ; 
 int /*<<< orphan*/  WIFSTOPPED (int) ; 
 scalar_t__ WSTOPSIG (int) ; 
 int /*<<< orphan*/  WUNTRACED ; 
 int /*<<< orphan*/  fatal (char*,int) ; 
 int /*<<< orphan*/  fatal_perror (char*) ; 
 int fork () ; 
 int /*<<< orphan*/  ptrace_child () ; 
 int waitpid (int,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int start_ptraced_child(void)
{
	int pid, n, status;

	pid = fork();
	if (pid == 0)
		ptrace_child();
	else if (pid < 0)
		fatal_perror("start_ptraced_child : fork failed");

	CATCH_EINTR(n = waitpid(pid, &status, WUNTRACED));
	if (n < 0)
		fatal_perror("check_ptrace : waitpid failed");
	if (!WIFSTOPPED(status) || (WSTOPSIG(status) != SIGSTOP))
		fatal("check_ptrace : expected SIGSTOP, got status = %d",
		      status);

	return pid;
}