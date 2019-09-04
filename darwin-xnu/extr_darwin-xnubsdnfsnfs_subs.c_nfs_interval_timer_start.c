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
typedef  int /*<<< orphan*/  thread_call_t ;

/* Variables and functions */
 int /*<<< orphan*/  clock_interval_to_deadline (int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  thread_call_enter_delayed (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
nfs_interval_timer_start(thread_call_t call, int interval)
{
	uint64_t deadline;

	clock_interval_to_deadline(interval, 1000 * 1000, &deadline);
	thread_call_enter_delayed(call, deadline);
}