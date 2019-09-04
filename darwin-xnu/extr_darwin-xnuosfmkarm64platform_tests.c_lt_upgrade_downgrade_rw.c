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
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  lck_rw_done (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_rw_lock_exclusive (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_rw_lock_exclusive_to_shared (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_rw_lock_shared (int /*<<< orphan*/ *) ; 
 scalar_t__ lck_rw_lock_shared_to_exclusive (int /*<<< orphan*/ *) ; 
 scalar_t__ lck_rw_try_lock_exclusive (int /*<<< orphan*/ *) ; 
 scalar_t__ lck_rw_try_lock_shared (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lt_counter ; 
 scalar_t__ lt_max_upgrade_holders ; 
 int /*<<< orphan*/  lt_note_another_blocking_lock_holder () ; 
 int /*<<< orphan*/  lt_note_blocking_lock_release () ; 
 int /*<<< orphan*/  lt_rwlock ; 
 int /*<<< orphan*/  lt_sleep_a_little_bit () ; 
 int /*<<< orphan*/  lt_spin_a_little_bit () ; 
 scalar_t__ lt_upgrade_holders ; 

__attribute__((used)) static void
lt_upgrade_downgrade_rw() 
{
	boolean_t upgraded, success;

	success = lck_rw_try_lock_shared(&lt_rwlock);
	if (!success) {
		lck_rw_lock_shared(&lt_rwlock);
	}

	lt_note_another_blocking_lock_holder();
	lt_sleep_a_little_bit();
	lt_note_blocking_lock_release();
	
	upgraded = lck_rw_lock_shared_to_exclusive(&lt_rwlock);
	if (!upgraded) {
		success = lck_rw_try_lock_exclusive(&lt_rwlock);

		if (!success) {
			lck_rw_lock_exclusive(&lt_rwlock);
		}
	}

	lt_upgrade_holders++;
	if (lt_upgrade_holders > lt_max_upgrade_holders) {
		lt_max_upgrade_holders = lt_upgrade_holders;
	}

	lt_counter++;
	lt_sleep_a_little_bit();

	lt_upgrade_holders--;
	
	lck_rw_lock_exclusive_to_shared(&lt_rwlock);

	lt_spin_a_little_bit();
	lck_rw_done(&lt_rwlock);
}