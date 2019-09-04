#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  hwlock; } ;
typedef  TYPE_1__ lck_spin_t ;

/* Variables and functions */
 int /*<<< orphan*/  hw_lock_lock (int /*<<< orphan*/ *) ; 

void
lck_spin_lock(lck_spin_t *lock)
{
#if	DEVELOPMENT || DEBUG
	if (lock->type != LCK_SPIN_TYPE)
		panic("Invalid spinlock %p", lock);
#endif	// DEVELOPMENT || DEBUG
	hw_lock_lock(&lock->hwlock);
}