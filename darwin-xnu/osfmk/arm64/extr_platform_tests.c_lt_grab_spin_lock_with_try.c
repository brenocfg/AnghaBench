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
 scalar_t__ lck_spin_try_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lt_counter ; 
 int /*<<< orphan*/  lt_lck_spin_t ; 
 int /*<<< orphan*/  lt_spin_a_little_bit () ; 

__attribute__((used)) static void
lt_grab_spin_lock_with_try() 
{
	while(0 == lck_spin_try_lock(&lt_lck_spin_t));
	lt_counter++;
	lt_spin_a_little_bit();
	lck_spin_unlock(&lt_lck_spin_t);
}