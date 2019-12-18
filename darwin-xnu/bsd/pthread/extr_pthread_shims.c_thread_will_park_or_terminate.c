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
typedef  int /*<<< orphan*/  thread_t ;

/* Variables and functions */
 int /*<<< orphan*/  kevent_exit_on_workloop_ownership_leak (int /*<<< orphan*/ ) ; 
 scalar_t__ thread_owned_workloops_count (int /*<<< orphan*/ ) ; 

void
thread_will_park_or_terminate(thread_t thread)
{
	if (thread_owned_workloops_count(thread)) {
		(void)kevent_exit_on_workloop_ownership_leak(thread);
	}
}