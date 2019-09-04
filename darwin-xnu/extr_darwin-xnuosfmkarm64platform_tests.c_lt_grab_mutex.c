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
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lt_counter ; 
 int /*<<< orphan*/  lt_mtx ; 
 int /*<<< orphan*/  lt_note_another_blocking_lock_holder () ; 
 int /*<<< orphan*/  lt_note_blocking_lock_release () ; 
 int /*<<< orphan*/  lt_sleep_a_little_bit () ; 

__attribute__((used)) static void
lt_grab_mutex() 
{
	lck_mtx_lock(&lt_mtx);
	lt_note_another_blocking_lock_holder();
	lt_sleep_a_little_bit();
	lt_counter++;
	lt_note_blocking_lock_release();
	lck_mtx_unlock(&lt_mtx);
}