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
typedef  scalar_t__ uint64_t ;
typedef  scalar_t__ int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  T_LOG (char*,int) ; 
 int llabs (scalar_t__) ; 
 int /*<<< orphan*/  run_sleep_tests ; 
 int /*<<< orphan*/  sleep (int) ; 
 scalar_t__ time_delta_ms () ; 

__attribute__((used)) static int wait_for_sleep() {
	if(!run_sleep_tests) return 0;

	uint64_t before_diff = time_delta_ms();
	
	for(int i = 0; i < 30; i++) {
		uint64_t after_diff = time_delta_ms();

		// on OSX, there's enough latency between calls to MCT and MAT
		// when the system is going down for sleep for values to diverge a few ms
		if(llabs((int64_t)before_diff - (int64_t)after_diff) > 2) {
			return i + 1;
		}
		
		sleep(1);
		T_LOG("waited %d seconds for sleep...", i+1);
	}
	return -1;
}