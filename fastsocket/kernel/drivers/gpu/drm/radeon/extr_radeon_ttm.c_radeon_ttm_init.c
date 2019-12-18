#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  dev_mapping; } ;
struct TYPE_8__ {int /*<<< orphan*/  object; } ;
struct TYPE_9__ {TYPE_1__ ref; } ;
struct TYPE_11__ {int initialized; TYPE_6__ bdev; TYPE_2__ bo_global_ref; } ;
struct TYPE_10__ {int real_vram_size; int gtt_size; } ;
struct radeon_device {TYPE_5__* ddev; TYPE_4__ mman; TYPE_3__ mc; int /*<<< orphan*/  stollen_vga_memory; int /*<<< orphan*/  need_dma32; } ;
struct TYPE_12__ {int /*<<< orphan*/  dev_mapping; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,...) ; 
 int /*<<< orphan*/  DRM_FILE_PAGE_OFFSET ; 
 int /*<<< orphan*/  DRM_INFO (char*,unsigned int) ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  RADEON_GEM_DOMAIN_VRAM ; 
 int /*<<< orphan*/  TTM_PL_TT ; 
 int /*<<< orphan*/  TTM_PL_VRAM ; 
 int radeon_bo_create (struct radeon_device*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  radeon_bo_driver ; 
 int radeon_bo_pin (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int radeon_bo_reserve (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  radeon_bo_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  radeon_bo_unreserve (int /*<<< orphan*/ ) ; 
 int radeon_ttm_debugfs_init (struct radeon_device*) ; 
 int radeon_ttm_global_init (struct radeon_device*) ; 
 int ttm_bo_device_init (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ttm_bo_init_mm (TYPE_6__*,int /*<<< orphan*/ ,int) ; 

int radeon_ttm_init(struct radeon_device *rdev)
{
	int r;

	r = radeon_ttm_global_init(rdev);
	if (r) {
		return r;
	}
	/* No others user of address space so set it to 0 */
	r = ttm_bo_device_init(&rdev->mman.bdev,
			       rdev->mman.bo_global_ref.ref.object,
			       &radeon_bo_driver, DRM_FILE_PAGE_OFFSET,
			       rdev->need_dma32);
	if (r) {
		DRM_ERROR("failed initializing buffer object driver(%d).\n", r);
		return r;
	}
	rdev->mman.initialized = true;
	r = ttm_bo_init_mm(&rdev->mman.bdev, TTM_PL_VRAM,
				rdev->mc.real_vram_size >> PAGE_SHIFT);
	if (r) {
		DRM_ERROR("Failed initializing VRAM heap.\n");
		return r;
	}
	r = radeon_bo_create(rdev, 256 * 1024, PAGE_SIZE, true,
			     RADEON_GEM_DOMAIN_VRAM,
			     NULL, &rdev->stollen_vga_memory);
	if (r) {
		return r;
	}
	r = radeon_bo_reserve(rdev->stollen_vga_memory, false);
	if (r)
		return r;
	r = radeon_bo_pin(rdev->stollen_vga_memory, RADEON_GEM_DOMAIN_VRAM, NULL);
	radeon_bo_unreserve(rdev->stollen_vga_memory);
	if (r) {
		radeon_bo_unref(&rdev->stollen_vga_memory);
		return r;
	}
	DRM_INFO("radeon: %uM of VRAM memory ready\n",
		 (unsigned) (rdev->mc.real_vram_size / (1024 * 1024)));
	r = ttm_bo_init_mm(&rdev->mman.bdev, TTM_PL_TT,
				rdev->mc.gtt_size >> PAGE_SHIFT);
	if (r) {
		DRM_ERROR("Failed initializing GTT heap.\n");
		return r;
	}
	DRM_INFO("radeon: %uM of GTT memory ready.\n",
		 (unsigned)(rdev->mc.gtt_size / (1024 * 1024)));
	rdev->mman.bdev.dev_mapping = rdev->ddev->dev_mapping;

	r = radeon_ttm_debugfs_init(rdev);
	if (r) {
		DRM_ERROR("Failed to init debugfs\n");
		return r;
	}
	return 0;
}