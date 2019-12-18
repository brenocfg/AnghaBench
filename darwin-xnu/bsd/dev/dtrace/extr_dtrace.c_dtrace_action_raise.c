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
struct TYPE_2__ {scalar_t__ t_dtrace_sig; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_DTRACE_ILLOP ; 
 int /*<<< orphan*/  DTRACE_CPUFLAG_SET (int /*<<< orphan*/ ) ; 
 scalar_t__ NSIG ; 
 int /*<<< orphan*/  act_set_astbsd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_thread () ; 
 scalar_t__ dtrace_destructive_disallow ; 
 int /*<<< orphan*/  get_bsdthread_info (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dtrace_action_raise(uint64_t sig)
{
	if (dtrace_destructive_disallow)
		return;

	if (sig >= NSIG) {
		DTRACE_CPUFLAG_SET(CPU_DTRACE_ILLOP);
		return;
	}

	/*
	 * raise() has a queue depth of 1 -- we ignore all subsequent
	 * invocations of the raise() action.
	 */

	uthread_t uthread = (uthread_t)get_bsdthread_info(current_thread());

	if (uthread && uthread->t_dtrace_sig == 0) {
		uthread->t_dtrace_sig = sig;
		act_set_astbsd(current_thread());
	}
}