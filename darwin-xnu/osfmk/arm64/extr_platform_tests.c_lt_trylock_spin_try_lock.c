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
 int /*<<< orphan*/  OSMemoryBarrier () ; 
 int /*<<< orphan*/  lck_spin_try_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lt_lck_spin_t ; 
 int /*<<< orphan*/  lt_sleep_a_little_bit () ; 
 int /*<<< orphan*/  lt_thread_lock_grabbed ; 
 int /*<<< orphan*/  lt_thread_lock_success ; 

__attribute__((used)) static void
lt_trylock_spin_try_lock()
{
	OSMemoryBarrier();
	while (!lt_thread_lock_grabbed) {
		lt_sleep_a_little_bit();
		OSMemoryBarrier();
	}
	lt_thread_lock_success = lck_spin_try_lock(&lt_lck_spin_t);
	OSMemoryBarrier();
}