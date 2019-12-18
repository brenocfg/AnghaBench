#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int lock; } ;
typedef  TYPE_1__ raw_rwlock_t ;

/* Variables and functions */
 int /*<<< orphan*/  __raw_read_can_lock (TYPE_1__*) ; 
 unsigned int _raw_compare_and_swap (int*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  _raw_yield () ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int spin_retry ; 

void _raw_read_lock_wait_flags(raw_rwlock_t *rw, unsigned long flags)
{
	unsigned int old;
	int count = spin_retry;

	local_irq_restore(flags);
	while (1) {
		if (count-- <= 0) {
			_raw_yield();
			count = spin_retry;
		}
		if (!__raw_read_can_lock(rw))
			continue;
		old = rw->lock & 0x7fffffffU;
		local_irq_disable();
		if (_raw_compare_and_swap(&rw->lock, old, old + 1) == old)
			return;
	}
}