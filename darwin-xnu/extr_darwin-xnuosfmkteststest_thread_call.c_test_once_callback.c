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
typedef  scalar_t__ thread_call_param_t ;
typedef  int /*<<< orphan*/  test_param ;
typedef  int /*<<< orphan*/  kern_return_t ;

/* Variables and functions */
 int /*<<< orphan*/  LCK_SLEEP_DEFAULT ; 
 int /*<<< orphan*/  NSEC_PER_SEC ; 
 int TEST_ARG1 ; 
 int TEST_ARG2 ; 
 int THREAD_AWAKENED ; 
 int /*<<< orphan*/  THREAD_UNINT ; 
 int /*<<< orphan*/  T_ASSERT_EQ_INT (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  clock_interval_to_deadline (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  delay_for_interval (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_sleep_deadline (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  once_callback_counter ; 
 int /*<<< orphan*/  test_lock ; 
 int /*<<< orphan*/  thread_wakeup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_for_callback ; 
 int /*<<< orphan*/  wait_for_main ; 

__attribute__((used)) static void
test_once_callback(thread_call_param_t param0,
                   thread_call_param_t param1)
{
	T_ASSERT_EQ_INT((test_param)param0, TEST_ARG1, "param0 is correct");
	T_ASSERT_EQ_INT((test_param)param1, TEST_ARG2, "param1 is correct");

	once_callback_counter++;

	T_ASSERT_EQ_INT(once_callback_counter, 1, "only one callback");

	lck_mtx_lock(&test_lock);

	thread_wakeup(&wait_for_callback);

	uint64_t deadline;
	clock_interval_to_deadline(10, NSEC_PER_SEC, &deadline);

	kern_return_t kr;
	/* wait for the main thread to finish, time out after 10s */
	kr = lck_mtx_sleep_deadline(&test_lock, LCK_SLEEP_DEFAULT, &wait_for_main, THREAD_UNINT, deadline);
	T_ASSERT_EQ_INT(kr, THREAD_AWAKENED, " callback woken by main function");

	lck_mtx_unlock(&test_lock);

	/* sleep for 1s to let the main thread begin the cancel and wait */
	delay_for_interval(1, NSEC_PER_SEC);
}