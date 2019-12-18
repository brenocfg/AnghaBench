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
struct TYPE_2__ {int /*<<< orphan*/  next; int /*<<< orphan*/  prev; } ;
struct mutex {scalar_t__ owner; TYPE_1__ wait_list; struct mutex* magic; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_LOCKS_WARN_ON (int) ; 
 scalar_t__ current_thread_info () ; 
 int /*<<< orphan*/  debug_locks ; 
 int /*<<< orphan*/  mutex_clear_owner (struct mutex*) ; 
 scalar_t__ unlikely (int) ; 

void debug_mutex_unlock(struct mutex *lock)
{
	if (unlikely(!debug_locks))
		return;

	DEBUG_LOCKS_WARN_ON(lock->magic != lock);
	DEBUG_LOCKS_WARN_ON(lock->owner != current_thread_info());
	DEBUG_LOCKS_WARN_ON(!lock->wait_list.prev && !lock->wait_list.next);
	mutex_clear_owner(lock);
}