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
typedef  int /*<<< orphan*/  thread_t ;
typedef  int /*<<< orphan*/  thread_continue_t ;
struct lck_mtx_thread_arg {int /*<<< orphan*/ * other_thread; scalar_t__ my_locked; scalar_t__* other_locked; } ;
typedef  scalar_t__ kern_return_t ;
typedef  int /*<<< orphan*/  event_t ;

/* Variables and functions */
 scalar_t__ KERN_SUCCESS ; 
 int /*<<< orphan*/  TEST_MTX_LOCK_STATS ; 
 int /*<<< orphan*/  THREAD_AWAKENED ; 
 int /*<<< orphan*/  THREAD_CONTINUE_NULL ; 
 int /*<<< orphan*/  THREAD_UNINT ; 
 int /*<<< orphan*/  absolutetime_to_nanoseconds (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acquire ; 
 int /*<<< orphan*/  assert_wait (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_wait (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_thread () ; 
 scalar_t__ end_loop_time ; 
 scalar_t__ end_loop_time_run ; 
 int iterations ; 
 scalar_t__ kernel_thread_start (int /*<<< orphan*/ ,struct lck_mtx_thread_arg*,int /*<<< orphan*/ *) ; 
 int os_atomic_load (scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_atomic_xchg (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ print_test_mtx_stats_string_name (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  release ; 
 int snprintf (char*,int,char*,...) ; 
 scalar_t__ start_loop_time ; 
 scalar_t__ start_loop_time_run ; 
 scalar_t__ synch ; 
 scalar_t__ test_mtx_lck_unlock_contended_loop_time_thread ; 
 int /*<<< orphan*/  thread_block (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_deallocate (int /*<<< orphan*/ ) ; 
 scalar_t__ wait_barrier ; 

int
lck_mtx_test_mtx_contended_loop_time(
	int iter,
	char *buffer,
	int buffer_size)
{
	thread_t thread1, thread2;
	kern_return_t result;
	int ret;
	struct lck_mtx_thread_arg targs[2] = {};
	synch = 0;
	wait_barrier = 0;
	iterations = iter;
	uint64_t time, time_run;

	targs[0].other_thread = NULL;
	targs[1].other_thread = NULL;

	result = kernel_thread_start((thread_continue_t)test_mtx_lck_unlock_contended_loop_time_thread, &targs[0], &thread1);
	if (result != KERN_SUCCESS) {
		return 0;
	}

	result = kernel_thread_start((thread_continue_t)test_mtx_lck_unlock_contended_loop_time_thread, &targs[1], &thread2);
	if (result != KERN_SUCCESS) {
		thread_deallocate(thread1);
		return 0;
	}

	/* this are t1 args */
	targs[0].my_locked = 0;
	targs[0].other_locked = &targs[1].my_locked;

	os_atomic_xchg(&targs[0].other_thread, thread2, release);

	/* this are t2 args */
	targs[1].my_locked = 0;
	targs[1].other_locked = &targs[0].my_locked;

	os_atomic_xchg(&targs[1].other_thread, thread1, release);

	while (os_atomic_load(&wait_barrier, acquire) != 2) {
		assert_wait((event_t) &wait_barrier, THREAD_UNINT);
		if (os_atomic_load(&wait_barrier, acquire) != 2) {
			(void) thread_block(THREAD_CONTINUE_NULL);
		} else {
			clear_wait(current_thread(), THREAD_AWAKENED);
		}
	}

	thread_deallocate(thread1);
	thread_deallocate(thread2);

	absolutetime_to_nanoseconds(end_loop_time - start_loop_time, &time);
	absolutetime_to_nanoseconds(end_loop_time_run - start_loop_time_run, &time_run);

	ret = snprintf(buffer, buffer_size, "\n");
	ret += snprintf(&buffer[ret], buffer_size - ret, "total time %llu ns total run time %llu ns ", time, time_run);
	ret += print_test_mtx_stats_string_name(TEST_MTX_LOCK_STATS, &buffer[ret], buffer_size - ret);
	ret += snprintf(&buffer[ret], buffer_size - ret, "\n");

	return ret;
}