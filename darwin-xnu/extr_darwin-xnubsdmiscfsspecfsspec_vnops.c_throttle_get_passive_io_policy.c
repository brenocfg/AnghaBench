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
typedef  int /*<<< orphan*/  uthread_t ;

/* Variables and functions */
 int /*<<< orphan*/  TASK_POLICY_PASSIVE_IO ; 
 int /*<<< orphan*/  current_thread () ; 
 int /*<<< orphan*/  get_bsdthread_info (int /*<<< orphan*/ ) ; 
 int proc_get_effective_thread_policy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
throttle_get_passive_io_policy(uthread_t *ut)
{
	if (ut != NULL)
		*ut = get_bsdthread_info(current_thread());

	return (proc_get_effective_thread_policy(current_thread(), TASK_POLICY_PASSIVE_IO));
}