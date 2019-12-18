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
 int /*<<< orphan*/  CATCH_EINTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PTRACE_CONT ; 
 int /*<<< orphan*/  PTRACE_KILL ; 
 int /*<<< orphan*/  SIGKILL ; 
 int /*<<< orphan*/  __WALL ; 
 int /*<<< orphan*/  kill (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptrace (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  waitpid (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void os_kill_ptraced_process(int pid, int reap_child)
{
	kill(pid, SIGKILL);
	ptrace(PTRACE_KILL, pid);
	ptrace(PTRACE_CONT, pid);
	if (reap_child)
		CATCH_EINTR(waitpid(pid, NULL, __WALL));
}