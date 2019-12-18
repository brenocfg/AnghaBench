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
struct TYPE_2__ {int /*<<< orphan*/ * clear_state_obj; int /*<<< orphan*/  clear_state_gpu_addr; int /*<<< orphan*/ * save_restore_obj; int /*<<< orphan*/  save_restore_gpu_addr; } ;
struct radeon_device {int /*<<< orphan*/  dev; TYPE_1__ rlc; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  RADEON_GEM_DOMAIN_VRAM ; 
 int /*<<< orphan*/  RADEON_GPU_PAGE_SIZE ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int) ; 
 int radeon_bo_create (struct radeon_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int radeon_bo_pin (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int radeon_bo_reserve (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  radeon_bo_unreserve (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  si_rlc_fini (struct radeon_device*) ; 
 scalar_t__ unlikely (int) ; 

int si_rlc_init(struct radeon_device *rdev)
{
	int r;

	/* save restore block */
	if (rdev->rlc.save_restore_obj == NULL) {
		r = radeon_bo_create(rdev, RADEON_GPU_PAGE_SIZE, PAGE_SIZE, true,
				     RADEON_GEM_DOMAIN_VRAM, NULL,
				     &rdev->rlc.save_restore_obj);
		if (r) {
			dev_warn(rdev->dev, "(%d) create RLC sr bo failed\n", r);
			return r;
		}
	}

	r = radeon_bo_reserve(rdev->rlc.save_restore_obj, false);
	if (unlikely(r != 0)) {
		si_rlc_fini(rdev);
		return r;
	}
	r = radeon_bo_pin(rdev->rlc.save_restore_obj, RADEON_GEM_DOMAIN_VRAM,
			  &rdev->rlc.save_restore_gpu_addr);
	radeon_bo_unreserve(rdev->rlc.save_restore_obj);
	if (r) {
		dev_warn(rdev->dev, "(%d) pin RLC sr bo failed\n", r);
		si_rlc_fini(rdev);
		return r;
	}

	/* clear state block */
	if (rdev->rlc.clear_state_obj == NULL) {
		r = radeon_bo_create(rdev, RADEON_GPU_PAGE_SIZE, PAGE_SIZE, true,
				     RADEON_GEM_DOMAIN_VRAM, NULL,
				     &rdev->rlc.clear_state_obj);
		if (r) {
			dev_warn(rdev->dev, "(%d) create RLC c bo failed\n", r);
			si_rlc_fini(rdev);
			return r;
		}
	}
	r = radeon_bo_reserve(rdev->rlc.clear_state_obj, false);
	if (unlikely(r != 0)) {
		si_rlc_fini(rdev);
		return r;
	}
	r = radeon_bo_pin(rdev->rlc.clear_state_obj, RADEON_GEM_DOMAIN_VRAM,
			  &rdev->rlc.clear_state_gpu_addr);
	radeon_bo_unreserve(rdev->rlc.clear_state_obj);
	if (r) {
		dev_warn(rdev->dev, "(%d) pin RLC c bo failed\n", r);
		si_rlc_fini(rdev);
		return r;
	}

	return 0;
}