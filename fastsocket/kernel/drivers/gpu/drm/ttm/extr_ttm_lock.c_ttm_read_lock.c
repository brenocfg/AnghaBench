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
struct ttm_lock {int /*<<< orphan*/  queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  __ttm_read_lock (struct ttm_lock*) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int wait_event_interruptible (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int ttm_read_lock(struct ttm_lock *lock, bool interruptible)
{
	int ret = 0;

	if (interruptible)
		ret = wait_event_interruptible(lock->queue,
					       __ttm_read_lock(lock));
	else
		wait_event(lock->queue, __ttm_read_lock(lock));
	return ret;
}