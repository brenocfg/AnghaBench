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
struct drm_lock_data {scalar_t__ kernel_waiters; int /*<<< orphan*/  spinlock; scalar_t__ idle_has_lock; int /*<<< orphan*/  lock_queue; TYPE_1__* hw_lock; } ;
struct TYPE_2__ {unsigned int lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_KERNEL_CONTEXT ; 
 unsigned int cmpxchg (unsigned int volatile*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

void drm_idlelock_release(struct drm_lock_data *lock_data)
{
	unsigned int old, prev;
	volatile unsigned int *lock = &lock_data->hw_lock->lock;

	spin_lock_bh(&lock_data->spinlock);
	if (--lock_data->kernel_waiters == 0) {
		if (lock_data->idle_has_lock) {
			do {
				old = *lock;
				prev = cmpxchg(lock, old, DRM_KERNEL_CONTEXT);
			} while (prev != old);
			wake_up_interruptible(&lock_data->lock_queue);
			lock_data->idle_has_lock = 0;
		}
	}
	spin_unlock_bh(&lock_data->spinlock);
}