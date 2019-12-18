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
struct mutex_waiter {int /*<<< orphan*/  list; struct mutex_waiter* magic; } ;
struct mutex {int /*<<< orphan*/  wait_list; int /*<<< orphan*/  wait_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_LOCKS_WARN_ON (int) ; 
 int /*<<< orphan*/  SMP_DEBUG_LOCKS_WARN_ON (int) ; 
 int list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_is_locked (int /*<<< orphan*/ *) ; 

void debug_mutex_wake_waiter(struct mutex *lock, struct mutex_waiter *waiter)
{
	SMP_DEBUG_LOCKS_WARN_ON(!spin_is_locked(&lock->wait_lock));
	DEBUG_LOCKS_WARN_ON(list_empty(&lock->wait_list));
	DEBUG_LOCKS_WARN_ON(waiter->magic != waiter);
	DEBUG_LOCKS_WARN_ON(list_empty(&waiter->list));
}