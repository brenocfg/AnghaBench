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
struct TYPE_2__ {int t_dtrace_stop; } ;

/* Variables and functions */
 int /*<<< orphan*/  act_set_astbsd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_thread () ; 
 scalar_t__ dtrace_destructive_disallow ; 
 int /*<<< orphan*/  get_bsdthread_info (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dtrace_action_stop(void)
{
	if (dtrace_destructive_disallow)
		return;

        uthread_t uthread = (uthread_t)get_bsdthread_info(current_thread());
	if (uthread) {
		/*
		 * The currently running process will be set to task_suspend
		 * when it next leaves the kernel.
		*/
		uthread->t_dtrace_stop = 1;
		act_set_astbsd(current_thread());
	}
}