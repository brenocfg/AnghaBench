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
typedef  int /*<<< orphan*/  hw_lock_bit_t ;

/* Variables and functions */
 int /*<<< orphan*/  _enable_preemption () ; 
 int /*<<< orphan*/  hw_unlock_bit_internal (int /*<<< orphan*/ *,unsigned int) ; 

void
hw_unlock_bit(hw_lock_bit_t *lock, unsigned int bit)
{
	hw_unlock_bit_internal(lock, bit);
	_enable_preemption();
}