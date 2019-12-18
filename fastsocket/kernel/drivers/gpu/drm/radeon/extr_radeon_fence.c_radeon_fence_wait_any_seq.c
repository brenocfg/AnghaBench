#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct radeon_device {int /*<<< orphan*/  ring_lock; TYPE_2__* ring; TYPE_1__* fence_drv; int /*<<< orphan*/  dev; int /*<<< orphan*/  ddev; int /*<<< orphan*/  fence_queue; } ;
struct TYPE_4__ {int ready; } ;
struct TYPE_3__ {unsigned long last_activity; } ;

/* Variables and functions */
 int EDEADLK ; 
 int ENOENT ; 
 unsigned long RADEON_FENCE_JIFFIES_TIMEOUT ; 
 unsigned int RADEON_NUM_RINGS ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int radeon_fence_any_seq_signaled (struct radeon_device*,scalar_t__*) ; 
 int /*<<< orphan*/  radeon_irq_kms_sw_irq_get (struct radeon_device*,unsigned int) ; 
 int /*<<< orphan*/  radeon_irq_kms_sw_irq_put (struct radeon_device*,unsigned int) ; 
 scalar_t__ radeon_ring_is_lockup (struct radeon_device*,unsigned int,TYPE_2__*) ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  trace_radeon_fence_wait_begin (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  trace_radeon_fence_wait_end (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ unlikely (int) ; 
 int wait_event_interruptible_timeout (int /*<<< orphan*/ ,int,unsigned long) ; 
 int wait_event_timeout (int /*<<< orphan*/ ,int,unsigned long) ; 

__attribute__((used)) static int radeon_fence_wait_any_seq(struct radeon_device *rdev,
				     u64 *target_seq, bool intr)
{
	unsigned long timeout, last_activity, tmp;
	unsigned i, ring = RADEON_NUM_RINGS;
	bool signaled;
	int r;

	for (i = 0, last_activity = 0; i < RADEON_NUM_RINGS; ++i) {
		if (!target_seq[i]) {
			continue;
		}

		/* use the most recent one as indicator */
		if (time_after(rdev->fence_drv[i].last_activity, last_activity)) {
			last_activity = rdev->fence_drv[i].last_activity;
		}

		/* For lockup detection just pick the lowest ring we are
		 * actively waiting for
		 */
		if (i < ring) {
			ring = i;
		}
	}

	/* nothing to wait for ? */
	if (ring == RADEON_NUM_RINGS) {
		return -ENOENT;
	}

	while (!radeon_fence_any_seq_signaled(rdev, target_seq)) {
		timeout = jiffies - RADEON_FENCE_JIFFIES_TIMEOUT;
		if (time_after(last_activity, timeout)) {
			/* the normal case, timeout is somewhere before last_activity */
			timeout = last_activity - timeout;
		} else {
			/* either jiffies wrapped around, or no fence was signaled in the last 500ms
			 * anyway we will just wait for the minimum amount and then check for a lockup
			 */
			timeout = 1;
		}

		trace_radeon_fence_wait_begin(rdev->ddev, target_seq[ring]);
		for (i = 0; i < RADEON_NUM_RINGS; ++i) {
			if (target_seq[i]) {
				radeon_irq_kms_sw_irq_get(rdev, i);
			}
		}
		if (intr) {
			r = wait_event_interruptible_timeout(rdev->fence_queue,
				(signaled = radeon_fence_any_seq_signaled(rdev, target_seq)),
				timeout);
		} else {
			r = wait_event_timeout(rdev->fence_queue,
				(signaled = radeon_fence_any_seq_signaled(rdev, target_seq)),
				timeout);
		}
		for (i = 0; i < RADEON_NUM_RINGS; ++i) {
			if (target_seq[i]) {
				radeon_irq_kms_sw_irq_put(rdev, i);
			}
		}
		if (unlikely(r < 0)) {
			return r;
		}
		trace_radeon_fence_wait_end(rdev->ddev, target_seq[ring]);

		if (unlikely(!signaled)) {
			/* we were interrupted for some reason and fence
			 * isn't signaled yet, resume waiting */
			if (r) {
				continue;
			}

			mutex_lock(&rdev->ring_lock);
			for (i = 0, tmp = 0; i < RADEON_NUM_RINGS; ++i) {
				if (time_after(rdev->fence_drv[i].last_activity, tmp)) {
					tmp = rdev->fence_drv[i].last_activity;
				}
			}
			/* test if somebody else has already decided that this is a lockup */
			if (last_activity != tmp) {
				last_activity = tmp;
				mutex_unlock(&rdev->ring_lock);
				continue;
			}

			if (radeon_ring_is_lockup(rdev, ring, &rdev->ring[ring])) {
				/* good news we believe it's a lockup */
				dev_warn(rdev->dev, "GPU lockup (waiting for 0x%016llx)\n",
					 target_seq[ring]);

				/* change last activity so nobody else think there is a lockup */
				for (i = 0; i < RADEON_NUM_RINGS; ++i) {
					rdev->fence_drv[i].last_activity = jiffies;
				}

				/* mark the ring as not ready any more */
				rdev->ring[ring].ready = false;
				mutex_unlock(&rdev->ring_lock);
				return -EDEADLK;
			}
			mutex_unlock(&rdev->ring_lock);
		}
	}
	return 0;
}