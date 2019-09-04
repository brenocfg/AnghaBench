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
typedef  union sigval {int dummy; } sigval ;
typedef  int /*<<< orphan*/  sigset_t ;
struct TYPE_4__ {int si_signo; int /*<<< orphan*/  si_pid; int /*<<< orphan*/  si_uid; union sigval si_value; int /*<<< orphan*/  si_code; } ;
typedef  TYPE_1__ siginfo_t ;
typedef  int /*<<< orphan*/  pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  SI_QUEUE ; 
 int /*<<< orphan*/  SYS_rt_sigqueueinfo ; 
 int /*<<< orphan*/  __block_app_sigs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __restore_sigs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  getpid () ; 
 int /*<<< orphan*/  getuid () ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int syscall (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,TYPE_1__*) ; 

int sigqueue(pid_t pid, int sig, const union sigval value)
{
	siginfo_t si;
	sigset_t set;
	int r;
	memset(&si, 0, sizeof si);
	si.si_signo = sig;
	si.si_code = SI_QUEUE;
	si.si_value = value;
	si.si_uid = getuid();
	__block_app_sigs(&set);
	si.si_pid = getpid();
	r = syscall(SYS_rt_sigqueueinfo, pid, sig, &si);
	__restore_sigs(&set);
	return r;
}