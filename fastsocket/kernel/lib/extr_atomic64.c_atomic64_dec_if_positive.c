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
typedef  int /*<<< orphan*/  spinlock_t ;
struct TYPE_4__ {int counter; } ;
typedef  TYPE_1__ atomic64_t ;

/* Variables and functions */
 int /*<<< orphan*/ * lock_addr (TYPE_1__*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

long long atomic64_dec_if_positive(atomic64_t *v)
{
	unsigned long flags;
	spinlock_t *lock = lock_addr(v);
	long long val;

	spin_lock_irqsave(lock, flags);
	val = v->counter - 1;
	if (val >= 0)
		v->counter = val;
	spin_unlock_irqrestore(lock, flags);
	return val;
}