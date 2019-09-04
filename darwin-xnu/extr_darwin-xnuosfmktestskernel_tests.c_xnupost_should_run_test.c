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
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ int64_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int POSTARGS_CUSTOM_TEST_RUNLIST ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  get_range_bounds (char*,scalar_t__*,scalar_t__*) ; 
 int kernel_post_args ; 
 char* kernel_post_test_configs ; 

boolean_t
xnupost_should_run_test(uint32_t test_num)
{
	if (kernel_post_args & POSTARGS_CUSTOM_TEST_RUNLIST) {
		int64_t begin = 0, end = 999999;
		char * b = kernel_post_test_configs;
		while (*b) {
			get_range_bounds(b, &begin, &end);
			if (test_num >= begin && test_num <= end) {
				return TRUE;
			}

			/* skip to the next "," */
			while (*b != ',') {
				if (*b == '\0')
					return FALSE;
				b++;
			}
			/* skip past the ',' */
			b++;
		}
		return FALSE;
	}
	return TRUE;
}