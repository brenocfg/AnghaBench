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
typedef  TYPE_1__* uthread_t ;
typedef  scalar_t__ uint64_t ;
struct TYPE_2__ {scalar_t__ t_dtrace_resumepid; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_DTRACE_ILLOP ; 
 int /*<<< orphan*/  DTRACE_CPUFLAG_SET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  act_set_astbsd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_thread () ; 
 scalar_t__ dtrace_destructive_disallow ; 
 int /*<<< orphan*/  get_bsdthread_info (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kauth_cred_get () ; 
 scalar_t__ kauth_cred_issuser (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dtrace_action_pidresume(uint64_t pid)
{
	if (dtrace_destructive_disallow)
		return;

	if (kauth_cred_issuser(kauth_cred_get()) == 0) {
		DTRACE_CPUFLAG_SET(CPU_DTRACE_ILLOP);		
		return;
	}
        uthread_t uthread = (uthread_t)get_bsdthread_info(current_thread());

	/*
	 * When the currently running process leaves the kernel, it attempts to
	 * task_resume the process (denoted by pid), if that pid appears to have
	 * been stopped by dtrace_action_stop().
	 * The currently running process has a pidresume() queue depth of 1 --
	 * subsequent invocations of the pidresume() action are ignored.
	 */	

	if (pid != 0 && uthread && uthread->t_dtrace_resumepid == 0) {
		uthread->t_dtrace_resumepid = pid;
		act_set_astbsd(current_thread());
	}
}