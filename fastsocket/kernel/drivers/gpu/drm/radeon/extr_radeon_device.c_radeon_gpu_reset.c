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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_2__ {int /*<<< orphan*/  bdev; } ;
struct radeon_device {int /*<<< orphan*/  exclusive_lock; int /*<<< orphan*/  dev; TYPE_1__ mman; int /*<<< orphan*/  ddev; int /*<<< orphan*/ * ring; } ;

/* Variables and functions */
 int RADEON_NUM_RINGS ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_helper_resume_force_mode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int radeon_asic_reset (struct radeon_device*) ; 
 int /*<<< orphan*/  radeon_fence_driver_force_completion (struct radeon_device*) ; 
 int radeon_ib_ring_tests (struct radeon_device*) ; 
 int /*<<< orphan*/  radeon_restore_bios_scratch_regs (struct radeon_device*) ; 
 int /*<<< orphan*/  radeon_resume (struct radeon_device*) ; 
 unsigned int radeon_ring_backup (struct radeon_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  radeon_ring_restore (struct radeon_device*,int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  radeon_save_bios_scratch_regs (struct radeon_device*) ; 
 int /*<<< orphan*/  radeon_suspend (struct radeon_device*) ; 
 int ttm_bo_lock_delayed_workqueue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ttm_bo_unlock_delayed_workqueue (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

int radeon_gpu_reset(struct radeon_device *rdev)
{
	unsigned ring_sizes[RADEON_NUM_RINGS];
	uint32_t *ring_data[RADEON_NUM_RINGS];

	bool saved = false;

	int i, r;
	int resched;

	down_write(&rdev->exclusive_lock);
	radeon_save_bios_scratch_regs(rdev);
	/* block TTM */
	resched = ttm_bo_lock_delayed_workqueue(&rdev->mman.bdev);
	radeon_suspend(rdev);

	for (i = 0; i < RADEON_NUM_RINGS; ++i) {
		ring_sizes[i] = radeon_ring_backup(rdev, &rdev->ring[i],
						   &ring_data[i]);
		if (ring_sizes[i]) {
			saved = true;
			dev_info(rdev->dev, "Saved %d dwords of commands "
				 "on ring %d.\n", ring_sizes[i], i);
		}
	}

retry:
	r = radeon_asic_reset(rdev);
	if (!r) {
		dev_info(rdev->dev, "GPU reset succeeded, trying to resume\n");
		radeon_resume(rdev);
	}

	radeon_restore_bios_scratch_regs(rdev);

	if (!r) {
		for (i = 0; i < RADEON_NUM_RINGS; ++i) {
			radeon_ring_restore(rdev, &rdev->ring[i],
					    ring_sizes[i], ring_data[i]);
			ring_sizes[i] = 0;
			ring_data[i] = NULL;
		}

		r = radeon_ib_ring_tests(rdev);
		if (r) {
			dev_err(rdev->dev, "ib ring test failed (%d).\n", r);
			if (saved) {
				saved = false;
				radeon_suspend(rdev);
				goto retry;
			}
		}
	} else {
		radeon_fence_driver_force_completion(rdev);
		for (i = 0; i < RADEON_NUM_RINGS; ++i) {
			kfree(ring_data[i]);
		}
	}

	drm_helper_resume_force_mode(rdev->ddev);

	ttm_bo_unlock_delayed_workqueue(&rdev->mman.bdev, resched);
	if (r) {
		/* bad news, how to tell it to userspace ? */
		dev_info(rdev->dev, "GPU reset failed\n");
	}

	up_write(&rdev->exclusive_lock);
	return r;
}