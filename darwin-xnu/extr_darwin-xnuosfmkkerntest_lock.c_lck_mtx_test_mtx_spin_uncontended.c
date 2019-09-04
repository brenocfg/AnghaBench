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
typedef  int /*<<< orphan*/  kern_return_t ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int WARMUP_ITER ; 
 int /*<<< orphan*/  disable_all_test_mtx_stats () ; 
 int /*<<< orphan*/  enable_all_test_mtx_stats () ; 
 int /*<<< orphan*/  lck_mtx_test_lock_spin () ; 
 int /*<<< orphan*/  lck_mtx_test_lock_spin_always () ; 
 int /*<<< orphan*/  lck_mtx_test_try_lock_spin () ; 
 int /*<<< orphan*/  lck_mtx_test_try_lock_spin_always () ; 
 int /*<<< orphan*/  lck_mtx_test_unlock_spin () ; 

__attribute__((used)) static kern_return_t
lck_mtx_test_mtx_spin_uncontended(
	int iter)
{
	int i;

	disable_all_test_mtx_stats();

	//warming up the test for lock_spin
	for (i = 0; i < WARMUP_ITER; i++) {
		lck_mtx_test_lock_spin();
		lck_mtx_test_unlock_spin();
	}

	enable_all_test_mtx_stats();

	for (i = 0; i < iter; i++) {
		lck_mtx_test_lock_spin();
		lck_mtx_test_unlock_spin();
	}

	disable_all_test_mtx_stats();

	//warming up the test for try_lock_spin
	for (i = 0; i < WARMUP_ITER; i++) {
		lck_mtx_test_try_lock_spin();
		lck_mtx_test_unlock_spin();
	}

	enable_all_test_mtx_stats();

	for (i = 0; i < iter; i++) {
		lck_mtx_test_try_lock_spin();
		lck_mtx_test_unlock_spin();
	}

	disable_all_test_mtx_stats();

	//warming up the test for lock_spin_always
	for (i = 0; i < WARMUP_ITER; i++) {
		lck_mtx_test_lock_spin_always();
		lck_mtx_test_unlock_spin();
	}

	enable_all_test_mtx_stats();

	for (i = 0; i < iter; i++) {
		lck_mtx_test_lock_spin_always();
		lck_mtx_test_unlock_spin();
	}

	disable_all_test_mtx_stats();

	//warming up the test for try_lock_spin_always
	for (i = 0; i < WARMUP_ITER; i++) {
		lck_mtx_test_try_lock_spin_always();
		lck_mtx_test_unlock_spin();
	}

	enable_all_test_mtx_stats();

	for (i = 0; i < iter; i++) {
		lck_mtx_test_try_lock_spin_always();
		lck_mtx_test_unlock_spin();
	}

	return KERN_SUCCESS;
}