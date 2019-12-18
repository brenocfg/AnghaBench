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
struct radeon_device {TYPE_1__* ring; } ;
struct TYPE_2__ {int /*<<< orphan*/  rptr_save_reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  DRM_INFO (char*) ; 
 size_t RADEON_RING_TYPE_GFX_INDEX ; 
 int /*<<< orphan*/  r100_cp_disable (struct radeon_device*) ; 
 scalar_t__ r100_cp_wait_for_idle (struct radeon_device*) ; 
 int /*<<< orphan*/  radeon_ring_fini (struct radeon_device*,TYPE_1__*) ; 
 int /*<<< orphan*/  radeon_scratch_free (struct radeon_device*,int /*<<< orphan*/ ) ; 

void r100_cp_fini(struct radeon_device *rdev)
{
	if (r100_cp_wait_for_idle(rdev)) {
		DRM_ERROR("Wait for CP idle timeout, shutting down CP.\n");
	}
	/* Disable ring */
	r100_cp_disable(rdev);
	radeon_scratch_free(rdev, rdev->ring[RADEON_RING_TYPE_GFX_INDEX].rptr_save_reg);
	radeon_ring_fini(rdev, &rdev->ring[RADEON_RING_TYPE_GFX_INDEX]);
	DRM_INFO("radeon: cp finalized\n");
}