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
struct radeon_device {int /*<<< orphan*/  ring_lock; TYPE_1__* fence_drv; int /*<<< orphan*/  fence_queue; } ;
struct TYPE_2__ {int initialized; int /*<<< orphan*/  scratch_reg; } ;

/* Variables and functions */
 int RADEON_NUM_RINGS ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  radeon_fence_driver_force_completion (struct radeon_device*) ; 
 int radeon_fence_wait_empty_locked (struct radeon_device*,int) ; 
 int /*<<< orphan*/  radeon_scratch_free (struct radeon_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up_all (int /*<<< orphan*/ *) ; 

void radeon_fence_driver_fini(struct radeon_device *rdev)
{
	int ring, r;

	mutex_lock(&rdev->ring_lock);
	for (ring = 0; ring < RADEON_NUM_RINGS; ring++) {
		if (!rdev->fence_drv[ring].initialized)
			continue;
		r = radeon_fence_wait_empty_locked(rdev, ring);
		if (r) {
			/* no need to trigger GPU reset as we are unloading */
			radeon_fence_driver_force_completion(rdev);
		}
		wake_up_all(&rdev->fence_queue);
		radeon_scratch_free(rdev, rdev->fence_drv[ring].scratch_reg);
		rdev->fence_drv[ring].initialized = false;
	}
	mutex_unlock(&rdev->ring_lock);
}