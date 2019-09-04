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
 size_t TEST_MTX_LOCK_SPIN_ALWAYS_STATS ; 
 size_t TEST_MTX_LOCK_SPIN_STATS ; 
 size_t TEST_MTX_LOCK_STATS ; 
 int TEST_MTX_MAX_STATS ; 
 size_t TEST_MTX_TRY_LOCK_SPIN_ALWAYS_STATS ; 
 size_t TEST_MTX_TRY_LOCK_SPIN_STATS ; 
 size_t TEST_MTX_TRY_LOCK_STATS ; 
 int WARMUP_ITER ; 
 int /*<<< orphan*/  absolutetime_to_nanoseconds (scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_lock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_lock_spin_always (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_try_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_try_lock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_try_lock_spin_always (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ mach_absolute_time () ; 
 int print_test_mtx_stats_string_name (int,char*,int) ; 
 int snprintf (char*,int,char*,...) ; 
 int /*<<< orphan*/  test_mtx ; 
 scalar_t__ thread_get_runtime_self () ; 

int
lck_mtx_test_mtx_uncontended_loop_time(
	int iter, char *buffer, int size)
{
	int i;
	uint64_t tot_time[TEST_MTX_MAX_STATS];
	uint64_t run_time[TEST_MTX_MAX_STATS];
	uint64_t start;
	uint64_t start_run;

	//warming up the test
	for (i = 0; i < WARMUP_ITER; i++) {
		lck_mtx_lock(&test_mtx);
		lck_mtx_unlock(&test_mtx);
	}

	start_run = thread_get_runtime_self();
	start = mach_absolute_time();

	for (i = 0; i < iter; i++) {
		lck_mtx_lock(&test_mtx);
		lck_mtx_unlock(&test_mtx);
	}

	absolutetime_to_nanoseconds(mach_absolute_time() - start, &tot_time[TEST_MTX_LOCK_STATS]);
	absolutetime_to_nanoseconds(thread_get_runtime_self() - start_run, &run_time[TEST_MTX_LOCK_STATS]);

	//warming up the test
	for (i = 0; i < WARMUP_ITER; i++) {
		lck_mtx_try_lock(&test_mtx);
		lck_mtx_unlock(&test_mtx);
	}

	start_run = thread_get_runtime_self();
	start = mach_absolute_time();

	for (i = 0; i < iter; i++) {
		lck_mtx_try_lock(&test_mtx);
		lck_mtx_unlock(&test_mtx);
	}

	absolutetime_to_nanoseconds(mach_absolute_time() - start, &tot_time[TEST_MTX_TRY_LOCK_STATS]);
	absolutetime_to_nanoseconds(thread_get_runtime_self() - start_run, &run_time[TEST_MTX_TRY_LOCK_STATS]);

	//warming up the test
	for (i = 0; i < WARMUP_ITER; i++) {
		lck_mtx_lock_spin(&test_mtx);
		lck_mtx_unlock(&test_mtx);
	}

	start_run = thread_get_runtime_self();
	start = mach_absolute_time();

	for (i = 0; i < iter; i++) {
		lck_mtx_lock_spin(&test_mtx);
		lck_mtx_unlock(&test_mtx);
	}

	absolutetime_to_nanoseconds(mach_absolute_time() - start, &tot_time[TEST_MTX_LOCK_SPIN_STATS]);
	absolutetime_to_nanoseconds(thread_get_runtime_self() - start_run, &run_time[TEST_MTX_LOCK_SPIN_STATS]);

	//warming up the test
	for (i = 0; i < WARMUP_ITER; i++) {
		lck_mtx_lock_spin_always(&test_mtx);
		lck_mtx_unlock(&test_mtx);
	}

	start_run = thread_get_runtime_self();
	start = mach_absolute_time();

	for (i = 0; i < iter; i++) {
		lck_mtx_lock_spin_always(&test_mtx);
		lck_mtx_unlock(&test_mtx);
	}

	absolutetime_to_nanoseconds(mach_absolute_time() - start, &tot_time[TEST_MTX_LOCK_SPIN_ALWAYS_STATS]);
	absolutetime_to_nanoseconds(thread_get_runtime_self() - start_run, &run_time[TEST_MTX_LOCK_SPIN_ALWAYS_STATS]);

	//warming up the test
	for (i = 0; i < WARMUP_ITER; i++) {
		lck_mtx_try_lock_spin(&test_mtx);
		lck_mtx_unlock(&test_mtx);
	}

	start_run = thread_get_runtime_self();
	start = mach_absolute_time();

	for (i = 0; i < iter; i++) {
		lck_mtx_try_lock_spin(&test_mtx);
		lck_mtx_unlock(&test_mtx);
	}

	absolutetime_to_nanoseconds(mach_absolute_time() - start, &tot_time[TEST_MTX_TRY_LOCK_SPIN_STATS]);
	absolutetime_to_nanoseconds(thread_get_runtime_self() - start_run, &run_time[TEST_MTX_TRY_LOCK_SPIN_STATS]);

	//warming up the test
	for (i = 0; i < WARMUP_ITER; i++) {
		lck_mtx_try_lock_spin_always(&test_mtx);
		lck_mtx_unlock(&test_mtx);
	}

	start_run = thread_get_runtime_self();
	start = mach_absolute_time();

	for (i = 0; i < iter; i++) {
		lck_mtx_try_lock_spin_always(&test_mtx);
		lck_mtx_unlock(&test_mtx);
	}

	absolutetime_to_nanoseconds(mach_absolute_time() - start, &tot_time[TEST_MTX_TRY_LOCK_SPIN_ALWAYS_STATS]);
	absolutetime_to_nanoseconds(thread_get_runtime_self() - start_run, &run_time[TEST_MTX_TRY_LOCK_SPIN_ALWAYS_STATS]);

	int string_off = 0;
	int ret = 0;

	ret = snprintf(&buffer[string_off], size, "\n");
	size -= ret;
	string_off += ret;

	for (i = 0; i < TEST_MTX_MAX_STATS - 2; i++) {

		ret = snprintf(&buffer[string_off], size, "total time %llu ns total run time %llu ns ", tot_time[i], run_time[i]);
		size -= ret;
		string_off += ret;

		ret = print_test_mtx_stats_string_name(i, &buffer[string_off], size);
		size -= ret;
		string_off += ret;

		ret = snprintf(&buffer[string_off], size, "\n");
		size -= ret;
		string_off += ret;
	}

	return string_off;
}