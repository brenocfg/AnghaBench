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
typedef  scalar_t__ u64 ;

/* Variables and functions */
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 

unsigned long long cmpxchg_486_u64(volatile void *ptr, u64 old, u64 new)
{
	u64 prev;
	unsigned long flags;

	/* Poor man's cmpxchg8b for 386 and 486. Unsuitable for SMP */
	local_irq_save(flags);
	prev = *(u64 *)ptr;
	if (prev == old)
		*(u64 *)ptr = new;
	local_irq_restore(flags);
	return prev;
}