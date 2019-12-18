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
 int KTEST_MAXVARS ; 
 scalar_t__ T_RESULT_FAIL ; 
 scalar_t__ T_RESULT_PASS ; 
 scalar_t__ T_RESULT_UXPASS ; 
 scalar_t__ T_RESULT_XFAIL ; 
 char* ktest_current_expr ; 
 char* ktest_current_msg ; 
 int /*<<< orphan*/  ktest_current_time ; 
 scalar_t__ ktest_current_var_index ; 
 char** ktest_current_var_names ; 
 char** ktest_current_var_values ; 
 int /*<<< orphan*/  ktest_emit_testcase () ; 
 scalar_t__ ktest_expectfail ; 
 int /*<<< orphan*/  ktest_expression_index ; 
 int /*<<< orphan*/  ktest_failcount ; 
 char* ktest_output_buf ; 
 int /*<<< orphan*/  ktest_passcount ; 
 scalar_t__ ktest_quiet ; 
 scalar_t__ ktest_testcase_result ; 
 int /*<<< orphan*/  ktest_update_test_result_state () ; 
 int /*<<< orphan*/  ktest_xfailcount ; 
 int /*<<< orphan*/  ktest_xpasscount ; 
 int /*<<< orphan*/  mach_absolute_time () ; 

void
ktest_testcase(int success)
{
	ktest_current_time = mach_absolute_time();

	if(success && !ktest_expectfail) {
		/* PASS */
		ktest_passcount++;
		ktest_testcase_result = T_RESULT_PASS;
	} else if(!success && !ktest_expectfail) {
		/* FAIL */
		ktest_failcount++;
		ktest_testcase_result = T_RESULT_FAIL;
	} else if(success && ktest_expectfail) {
		/* UXPASS */
		ktest_xpasscount++;
		ktest_testcase_result = T_RESULT_UXPASS;
	} else if(!success && ktest_expectfail) {
		/* XFAIL */
		ktest_xfailcount++;
		ktest_testcase_result = T_RESULT_XFAIL;
	}

	ktest_update_test_result_state();
	if(ktest_quiet == 0 ||
	   ktest_testcase_result == T_RESULT_FAIL ||
	   ktest_testcase_result == T_RESULT_UXPASS) {
		ktest_emit_testcase();
	}
	ktest_expression_index++;

	ktest_quiet = 0;
	ktest_expectfail = 0;
	ktest_output_buf[0] = '\0';
	ktest_current_msg[0] = '\0';
	ktest_current_expr[0] = '\0';
	for(int i = 0; i < KTEST_MAXVARS; i++) {
		ktest_current_var_names[i][0] = '\0';
		ktest_current_var_values[i][0] = '\0';
	}
	ktest_current_var_index = 0;
}