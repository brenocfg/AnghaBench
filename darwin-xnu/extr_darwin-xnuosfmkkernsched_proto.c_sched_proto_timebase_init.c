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
typedef  int uint64_t ;
typedef  scalar_t__ uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  NSEC_PER_USEC ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  clock_interval_to_absolutetime_interval (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int default_timeshare_computation ; 
 int default_timeshare_constraint ; 
 int max_unsafe_computation ; 
 int max_unsafe_quanta ; 
 int proto_quantum ; 
 int /*<<< orphan*/  proto_quantum_us ; 
 int sched_safe_duration ; 
 int thread_depress_time ; 

__attribute__((used)) static void
sched_proto_timebase_init(void)
{
	uint64_t	abstime;

	/* standard timeslicing quantum */
	clock_interval_to_absolutetime_interval(
											proto_quantum_us, NSEC_PER_USEC, &abstime);
	assert((abstime >> 32) == 0 && (uint32_t)abstime != 0);
	proto_quantum = (uint32_t)abstime;
	
	thread_depress_time = 1 * proto_quantum;
	default_timeshare_computation = proto_quantum / 2;
	default_timeshare_constraint = proto_quantum;
	
	max_unsafe_computation = max_unsafe_quanta * proto_quantum;
	sched_safe_duration = 2 * max_unsafe_quanta * proto_quantum;

}