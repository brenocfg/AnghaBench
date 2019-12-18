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

/* Variables and functions */
 size_t ktest_test_result ; 
 size_t*** ktest_test_result_statetab ; 
 size_t ktest_testcase_mode ; 
 size_t ktest_testcase_result ; 

void
ktest_update_test_result_state(void) {
	ktest_test_result = ktest_test_result_statetab[ktest_test_result]
				 		      [ktest_testcase_result]
						      [ktest_testcase_mode];
}