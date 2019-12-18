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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  hw_lock_bit_t ;

/* Variables and functions */
 int /*<<< orphan*/  _disable_preemption () ; 
 unsigned int hw_lock_bit_to_internal (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ) ; 

unsigned int
hw_lock_bit_to(hw_lock_bit_t *lock, unsigned int bit, uint32_t timeout)
{
	_disable_preemption();
	return hw_lock_bit_to_internal(lock, bit, timeout);
}