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
struct TYPE_2__ {int member_0; } ;
typedef  TYPE_1__ thread_precedence_policy_data_t ;
typedef  int /*<<< orphan*/  thread_policy_t ;

/* Variables and functions */
 int /*<<< orphan*/  THREAD_PRECEDENCE_POLICY ; 
 int /*<<< orphan*/  THREAD_PRECEDENCE_POLICY_COUNT ; 
 int /*<<< orphan*/  fasttrap_cleanup_thread ; 
 int fasttrap_max ; 
 int fasttrap_retired ; 
 int fasttrap_total ; 
 int /*<<< orphan*/  thread_policy_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
fasttrap_pid_cleanup_compute_priority(void)
{
	if (fasttrap_total > (fasttrap_max / 100 * 90) || fasttrap_retired > fasttrap_max / 2) {
		thread_precedence_policy_data_t precedence = {12 /* BASEPRI_PREEMPT_HIGH */};
		thread_policy_set(fasttrap_cleanup_thread, THREAD_PRECEDENCE_POLICY, (thread_policy_t) &precedence, THREAD_PRECEDENCE_POLICY_COUNT);
	}
	else {
		thread_precedence_policy_data_t precedence = {-39 /* BASEPRI_USER_INITIATED */};
		thread_policy_set(fasttrap_cleanup_thread, THREAD_PRECEDENCE_POLICY, (thread_policy_t) &precedence, THREAD_PRECEDENCE_POLICY_COUNT);

	}
}