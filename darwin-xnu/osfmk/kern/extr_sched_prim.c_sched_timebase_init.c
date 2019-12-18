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
typedef  int /*<<< orphan*/  SCHED ;

/* Variables and functions */
 int /*<<< orphan*/  NSEC_PER_SEC ; 
 int /*<<< orphan*/  clock_interval_to_absolutetime_interval (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sched_one_second_interval ; 
 int /*<<< orphan*/  sched_realtime_timebase_init () ; 

void
sched_timebase_init(void)
{
	uint64_t	abstime;
	
	clock_interval_to_absolutetime_interval(1, NSEC_PER_SEC, &abstime);
	sched_one_second_interval = abstime;
	
	SCHED(timebase_init)();
	sched_realtime_timebase_init();
}