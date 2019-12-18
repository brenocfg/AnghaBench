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
struct TYPE_2__ {int initialized; int /*<<< orphan*/  bdev; } ;
struct radeon_device {TYPE_1__ mman; scalar_t__ stollen_vga_memory; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_INFO (char*) ; 
 int /*<<< orphan*/  TTM_PL_TT ; 
 int /*<<< orphan*/  TTM_PL_VRAM ; 
 int radeon_bo_reserve (scalar_t__,int) ; 
 int /*<<< orphan*/  radeon_bo_unpin (scalar_t__) ; 
 int /*<<< orphan*/  radeon_bo_unref (scalar_t__*) ; 
 int /*<<< orphan*/  radeon_bo_unreserve (scalar_t__) ; 
 int /*<<< orphan*/  radeon_gart_fini (struct radeon_device*) ; 
 int /*<<< orphan*/  radeon_ttm_global_fini (struct radeon_device*) ; 
 int /*<<< orphan*/  ttm_bo_clean_mm (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ttm_bo_device_release (int /*<<< orphan*/ *) ; 

void radeon_ttm_fini(struct radeon_device *rdev)
{
	int r;

	if (!rdev->mman.initialized)
		return;
	if (rdev->stollen_vga_memory) {
		r = radeon_bo_reserve(rdev->stollen_vga_memory, false);
		if (r == 0) {
			radeon_bo_unpin(rdev->stollen_vga_memory);
			radeon_bo_unreserve(rdev->stollen_vga_memory);
		}
		radeon_bo_unref(&rdev->stollen_vga_memory);
	}
	ttm_bo_clean_mm(&rdev->mman.bdev, TTM_PL_VRAM);
	ttm_bo_clean_mm(&rdev->mman.bdev, TTM_PL_TT);
	ttm_bo_device_release(&rdev->mman.bdev);
	radeon_gart_fini(rdev);
	radeon_ttm_global_fini(rdev);
	rdev->mman.initialized = false;
	DRM_INFO("radeon: ttm finalized\n");
}