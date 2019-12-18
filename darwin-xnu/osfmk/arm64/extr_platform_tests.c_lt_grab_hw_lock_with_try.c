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
 scalar_t__ hw_lock_try (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hw_lock_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lt_counter ; 
 int /*<<< orphan*/  lt_hw_lock ; 
 int /*<<< orphan*/  lt_spin_a_little_bit () ; 

__attribute__((used)) static void
lt_grab_hw_lock_with_try()
{
	while(0 == hw_lock_try(&lt_hw_lock));
	lt_counter++;
	lt_spin_a_little_bit();
	hw_lock_unlock(&lt_hw_lock);
}