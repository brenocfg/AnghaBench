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
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  NSEC_PER_USEC ; 
 int /*<<< orphan*/  THREAD_CALL_DELAY_LEEWAY ; 
 int /*<<< orphan*/  clock_interval_to_absolutetime_interval (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clock_interval_to_deadline (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * necp_client_update_tcall ; 
 int /*<<< orphan*/  necp_timeout_leeway_microseconds ; 
 int /*<<< orphan*/  necp_timeout_microseconds ; 
 int /*<<< orphan*/  thread_call_enter_delayed_with_leeway (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
necp_update_all_clients(void)
{
	if (necp_client_update_tcall == NULL) {
		// Don't try to update clients if the module is not initialized
		return;
	}

	uint64_t deadline = 0;
	uint64_t leeway = 0;
	clock_interval_to_deadline(necp_timeout_microseconds, NSEC_PER_USEC, &deadline);
	clock_interval_to_absolutetime_interval(necp_timeout_leeway_microseconds, NSEC_PER_USEC, &leeway);

	thread_call_enter_delayed_with_leeway(necp_client_update_tcall, NULL,
										  deadline, leeway, THREAD_CALL_DELAY_LEEWAY);
}