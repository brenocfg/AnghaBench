#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  raw_lock; } ;
typedef  TYPE_1__ spinlock_t ;

/* Variables and functions */
 int /*<<< orphan*/  __raw_spin_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __spin_lock_debug (TYPE_1__*) ; 
 int /*<<< orphan*/  debug_spin_lock_after (TYPE_1__*) ; 
 int /*<<< orphan*/  debug_spin_lock_before (TYPE_1__*) ; 
 scalar_t__ unlikely (int) ; 

void _raw_spin_lock(spinlock_t *lock)
{
	debug_spin_lock_before(lock);
	if (unlikely(!__raw_spin_trylock(&lock->raw_lock)))
		__spin_lock_debug(lock);
	debug_spin_lock_after(lock);
}