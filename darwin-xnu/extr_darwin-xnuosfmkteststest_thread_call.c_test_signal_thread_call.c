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
typedef  int /*<<< orphan*/  thread_call_t ;
typedef  int /*<<< orphan*/  thread_call_param_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  NSEC_PER_MSEC ; 
 int /*<<< orphan*/  NSEC_PER_SEC ; 
 scalar_t__ TEST_ARG1 ; 
 scalar_t__ TEST_ARG2 ; 
 int THREAD_CALL_OPTIONS_ONCE ; 
 int THREAD_CALL_OPTIONS_SIGNAL ; 
 int /*<<< orphan*/  THREAD_CALL_PRIORITY_HIGH ; 
 int TRUE ; 
 int /*<<< orphan*/  T_ASSERT_EQ_INT (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  clock_interval_to_deadline (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  delay_for_interval (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  signal_callback_counter ; 
 int /*<<< orphan*/  test_signal_callback ; 
 int /*<<< orphan*/  thread_call_allocate_with_options (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  thread_call_cancel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_call_enter1_delayed (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_call_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
test_signal_thread_call(void)
{
	thread_call_t call;
	call = thread_call_allocate_with_options(&test_signal_callback,
	                                         (thread_call_param_t)TEST_ARG1,
	                                         THREAD_CALL_PRIORITY_HIGH,
	                                         THREAD_CALL_OPTIONS_ONCE|THREAD_CALL_OPTIONS_SIGNAL);

	thread_call_param_t arg2_param = (thread_call_param_t)TEST_ARG2;

	uint64_t deadline;

	boolean_t canceled, pending, freed;

	clock_interval_to_deadline(10, NSEC_PER_SEC, &deadline);
	pending = thread_call_enter1_delayed(call, arg2_param, deadline);
	T_ASSERT_EQ_INT(pending, FALSE, "call should not be pending");

	canceled = thread_call_cancel(call);
	T_ASSERT_EQ_INT(canceled, TRUE, "thread_call_cancel should succeed");

	clock_interval_to_deadline(10, NSEC_PER_MSEC, &deadline);
	pending = thread_call_enter1_delayed(call, arg2_param, deadline);
	T_ASSERT_EQ_INT(pending, FALSE, "call should not be pending");

	/* sleep for 50ms to let the interrupt fire */
	delay_for_interval(50, NSEC_PER_MSEC);

	T_ASSERT_EQ_INT(signal_callback_counter, 1, "callback fired");

	canceled = thread_call_cancel(call);
	T_ASSERT_EQ_INT(canceled, FALSE, "thread_call_cancel should not succeed");

	freed = thread_call_free(call);
	T_ASSERT_EQ_INT(freed, TRUE, "thread_call_free should succeed");
}