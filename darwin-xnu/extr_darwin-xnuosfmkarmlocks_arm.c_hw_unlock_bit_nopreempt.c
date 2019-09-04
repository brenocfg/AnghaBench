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
 scalar_t__ __improbable (int) ; 
 scalar_t__ get_preemption_level () ; 
 int /*<<< orphan*/  hw_unlock_bit_internal (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  panic (char*,int /*<<< orphan*/ *) ; 

void
hw_unlock_bit_nopreempt(hw_lock_bit_t *lock, unsigned int bit)
{
	if (__improbable(get_preemption_level() == 0))
		panic("Attempt to release no-preempt bitlock %p in preemptible context", lock);
	hw_unlock_bit_internal(lock, bit);
}