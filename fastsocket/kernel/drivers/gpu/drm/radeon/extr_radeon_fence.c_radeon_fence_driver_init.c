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
struct radeon_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  fence_queue; } ;

/* Variables and functions */
 int RADEON_NUM_RINGS ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 scalar_t__ radeon_debugfs_fence_init (struct radeon_device*) ; 
 int /*<<< orphan*/  radeon_fence_driver_init_ring (struct radeon_device*,int) ; 

int radeon_fence_driver_init(struct radeon_device *rdev)
{
	int ring;

	init_waitqueue_head(&rdev->fence_queue);
	for (ring = 0; ring < RADEON_NUM_RINGS; ring++) {
		radeon_fence_driver_init_ring(rdev, ring);
	}
	if (radeon_debugfs_fence_init(rdev)) {
		dev_err(rdev->dev, "fence debugfs file creation failed\n");
	}
	return 0;
}