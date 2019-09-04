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
 int /*<<< orphan*/  TASK_POLICY_INTERNAL ; 
 int /*<<< orphan*/  TASK_POLICY_IOPOL ; 
 int /*<<< orphan*/  current_thread () ; 
 int /*<<< orphan*/  proc_set_thread_policy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void throttle_set_thread_io_policy(int policy)
{
	proc_set_thread_policy(current_thread(), TASK_POLICY_INTERNAL, TASK_POLICY_IOPOL, policy);
}