#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* xnupost_test_t ;
typedef  size_t uint32_t ;
typedef  int kern_return_t ;
struct TYPE_3__ {int xt_config; scalar_t__ xt_retval; scalar_t__ xt_expected_retval; void* xt_test_actions; void* xt_end_time; int /*<<< orphan*/  (* xt_func ) () ;void* xt_begin_time; int /*<<< orphan*/  xt_name; } ;

/* Variables and functions */
 int KERN_SUCCESS ; 
 int POSTARGS_CONTROLLER_AVAILABLE ; 
 int POSTARGS_RUN_TESTS ; 
 int /*<<< orphan*/  T_BEGIN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  T_END ; 
 int /*<<< orphan*/  T_FINISH ; 
 int /*<<< orphan*/  T_SKIP (char*) ; 
 int /*<<< orphan*/  T_START ; 
 scalar_t__ T_TESTRESULT ; 
 void* XT_ACTION_FAILED ; 
 void* XT_ACTION_PASSED ; 
 void* XT_ACTION_SKIPPED ; 
 int XT_CONFIG_EXPECT_PANIC ; 
 int XT_CONFIG_IGNORE ; 
 int kernel_post_args ; 
 void* mach_absolute_time () ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  stub1 () ; 
 int /*<<< orphan*/  xnupost_reset_panic_widgets () ; 

kern_return_t
xnupost_run_tests(xnupost_test_t test_list, uint32_t test_count)
{
	uint32_t i = 0;
	int retval = KERN_SUCCESS;

	if ((kernel_post_args & POSTARGS_RUN_TESTS) == 0) {
		printf("No POST boot-arg set.\n");
		return retval;
	}

	T_START;
	xnupost_test_t testp;
	for (; i < test_count; i++) {
		xnupost_reset_panic_widgets();
		testp = &test_list[i];
		T_BEGIN(testp->xt_name);
		testp->xt_begin_time = mach_absolute_time();
		testp->xt_end_time   = testp->xt_begin_time;

		/*
		 * If test is designed to panic and controller
		 * is not available then mark as SKIPPED
		 */
		if ((testp->xt_config & XT_CONFIG_EXPECT_PANIC) && !(kernel_post_args & POSTARGS_CONTROLLER_AVAILABLE)) {
			T_SKIP(
			    "Test expects panic but "
			    "no controller is present");
			testp->xt_test_actions = XT_ACTION_SKIPPED;
			continue;
		}

		if ((testp->xt_config & XT_CONFIG_IGNORE)) {
			T_SKIP("Test is marked as XT_CONFIG_IGNORE");
			testp->xt_test_actions = XT_ACTION_SKIPPED;
			continue;
		}

		testp->xt_func();
		T_END;
		testp->xt_retval = T_TESTRESULT;
		testp->xt_end_time = mach_absolute_time();
		if (testp->xt_retval == testp->xt_expected_retval) {
			testp->xt_test_actions = XT_ACTION_PASSED;
		} else {
			testp->xt_test_actions = XT_ACTION_FAILED;
		}
	}
	T_FINISH;
	return retval;
}