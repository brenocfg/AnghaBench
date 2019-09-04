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
typedef  int /*<<< orphan*/  event_t ;

/* Variables and functions */
 int /*<<< orphan*/  THREAD_INTERRUPTIBLE ; 
 int /*<<< orphan*/  UDP_FLOW_GC_RUN_INTERVAL_NSEC ; 
 int /*<<< orphan*/  assert_wait (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert_wait_deadline (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cfil_sock_udp_attached_count ; 
 int /*<<< orphan*/  clock_absolutetime_interval_to_deadline (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nanoseconds_to_absolutetime (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
cfil_udp_gc_thread_sleep(bool forever)
{
	if (forever) {
		(void) assert_wait((event_t) &cfil_sock_udp_attached_count,
						   THREAD_INTERRUPTIBLE);
	} else {
		uint64_t deadline = 0;
		nanoseconds_to_absolutetime(UDP_FLOW_GC_RUN_INTERVAL_NSEC, &deadline);
		clock_absolutetime_interval_to_deadline(deadline, &deadline);

		(void) assert_wait_deadline(&cfil_sock_udp_attached_count,
									THREAD_INTERRUPTIBLE, deadline);
	}
}