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
struct ttm_lock {int /*<<< orphan*/  queue; int /*<<< orphan*/  lock; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  TTM_WRITE_LOCK_PENDING ; 
 int /*<<< orphan*/  __ttm_read_lock (struct ttm_lock*) ; 
 int /*<<< orphan*/  __ttm_write_lock (struct ttm_lock*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int wait_event_interruptible (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up_all (int /*<<< orphan*/ *) ; 

int ttm_write_lock(struct ttm_lock *lock, bool interruptible)
{
	int ret = 0;

	if (interruptible) {
		ret = wait_event_interruptible(lock->queue,
					       __ttm_write_lock(lock));
		if (unlikely(ret != 0)) {
			spin_lock(&lock->lock);
			lock->flags &= ~TTM_WRITE_LOCK_PENDING;
			wake_up_all(&lock->queue);
			spin_unlock(&lock->lock);
		}
	} else
		wait_event(lock->queue, __ttm_read_lock(lock));

	return ret;
}