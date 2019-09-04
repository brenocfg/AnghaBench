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
 int /*<<< orphan*/  LOCK_PANIC_TIMEOUT ; 
 scalar_t__ hw_lock_bit_to (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*,int /*<<< orphan*/ *) ; 

void
hw_lock_bit(hw_lock_bit_t *lock, unsigned int bit)
{
	if (hw_lock_bit_to(lock, bit, LOCK_PANIC_TIMEOUT))
		return;
#if	__SMP__
	panic("hw_lock_bit(): timed out (%p)", lock);
#else
	panic("hw_lock_bit(): interlock held (%p)", lock);
#endif
}