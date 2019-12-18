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
 scalar_t__ T_RESULT_FAIL ; 
 scalar_t__ T_RESULT_UXPASS ; 
 int /*<<< orphan*/  ktest_current_file ; 
 int /*<<< orphan*/  ktest_current_line ; 
 int /*<<< orphan*/  ktest_test_name ; 
 scalar_t__ ktest_testcase_result ; 
 int /*<<< orphan*/  ktest_testend () ; 
 int /*<<< orphan*/  panic (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
ktest_assertion_check(void) {
	if (ktest_testcase_result == T_RESULT_FAIL || ktest_testcase_result == T_RESULT_UXPASS) {
		ktest_testend();
		panic("XNUPOST: Assertion failed : %s : at %s:%d", ktest_test_name, ktest_current_file, ktest_current_line);
	}
}