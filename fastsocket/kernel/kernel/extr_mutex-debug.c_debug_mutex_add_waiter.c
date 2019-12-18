#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct thread_info {TYPE_1__* task; } ;
struct mutex_waiter {int dummy; } ;
struct mutex {int /*<<< orphan*/  wait_lock; } ;
struct TYPE_2__ {struct mutex_waiter* blocked_on; } ;

/* Variables and functions */
 int /*<<< orphan*/  SMP_DEBUG_LOCKS_WARN_ON (int) ; 
 int /*<<< orphan*/  spin_is_locked (int /*<<< orphan*/ *) ; 

void debug_mutex_add_waiter(struct mutex *lock, struct mutex_waiter *waiter,
			    struct thread_info *ti)
{
	SMP_DEBUG_LOCKS_WARN_ON(!spin_is_locked(&lock->wait_lock));

	/* Mark the current thread as blocked on the lock: */
	ti->task->blocked_on = waiter;
}