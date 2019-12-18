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

/* Variables and functions */
 int /*<<< orphan*/  bsd_post_tests ; 
 int /*<<< orphan*/  bsd_post_tests_count ; 
 int /*<<< orphan*/  delay (int) ; 
 scalar_t__ kernel_post_args ; 
 scalar_t__ last_loaded_timestamp ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int xnupost_list_tests (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
bsd_list_tests()
{
	if (kernel_post_args == 0) {
		return 0;
	}

	uint64_t prev_load_time    = last_loaded_timestamp;
	int no_load_counter        = 5;
	int absolute_break_counter = 15;
	int delay_duration_usecs   = 300000; /* 0.3 second for kext loading to stabilize */

	while (no_load_counter > 0) {
		printf("bsd_list_tests:INFO waiting for %d usecs\n", delay_duration_usecs);
		printf("bsd_list_tests: prev: %llu current: %llu\n", prev_load_time, last_loaded_timestamp);

		delay(delay_duration_usecs);
		absolute_break_counter -= 1;

		if (absolute_break_counter <= 0) {
			printf("bsd_list_tests: WARNING: Waiting beyond normal time for stabilizing kext loading\n");
			break;
		}

		if (prev_load_time == last_loaded_timestamp) {
			no_load_counter -= 1;
			printf("bsd_list_tests: INFO: no new kexts loaded. remaining checks: %d\n", no_load_counter);
		}

		prev_load_time = last_loaded_timestamp;
	}

	return xnupost_list_tests(bsd_post_tests, bsd_post_tests_count);
}