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
struct TYPE_4__ {long long counter; } ;
typedef  TYPE_1__ atomic64_t ;

/* Variables and functions */
 int /*<<< orphan*/ * lock_addr (TYPE_1__*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int atomic64_add_unless(atomic64_t *v, long long a, long long u)
{
	unsigned long flags;
	spinlock_t *lock = lock_addr(v);
	int ret = 1;

	spin_lock_irqsave(lock, flags);
	if (v->counter != u) {
		v->counter += a;
		ret = 0;
	}
	spin_unlock_irqrestore(lock, flags);
	return ret;
}