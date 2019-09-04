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
typedef  int /*<<< orphan*/  mach_msg_timeout_t ;

/* Variables and functions */
 int /*<<< orphan*/  NSEC_PER_MSEC ; 
 int /*<<< orphan*/  clock_interval_to_absolutetime_interval (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  thread_depress_abstime (int /*<<< orphan*/ ) ; 

void
thread_depress_ms(mach_msg_timeout_t interval)
{
	uint64_t abstime;

	clock_interval_to_absolutetime_interval(interval, NSEC_PER_MSEC, &abstime);
	thread_depress_abstime(abstime);
}