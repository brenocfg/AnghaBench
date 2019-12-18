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
struct radeon_surface_reg {struct radeon_bo* bo; } ;
struct radeon_device {struct radeon_surface_reg* surface_regs; } ;
struct TYPE_3__ {int start; } ;
struct TYPE_4__ {int num_pages; TYPE_1__ mem; } ;
struct radeon_bo {size_t surface_reg; scalar_t__ pin_count; TYPE_2__ tbo; int /*<<< orphan*/  pitch; int /*<<< orphan*/  tiling_flags; struct radeon_device* rdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  DRM_DEBUG (char*,int,struct radeon_bo*) ; 
 int ENOMEM ; 
 int PAGE_SHIFT ; 
 int RADEON_GEM_MAX_SURFACES ; 
 int /*<<< orphan*/  radeon_bo_is_reserved (struct radeon_bo*) ; 
 int /*<<< orphan*/  radeon_set_surface_reg (struct radeon_device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  ttm_bo_unmap_virtual (TYPE_2__*) ; 

int radeon_bo_get_surface_reg(struct radeon_bo *bo)
{
	struct radeon_device *rdev = bo->rdev;
	struct radeon_surface_reg *reg;
	struct radeon_bo *old_object;
	int steal;
	int i;

	BUG_ON(!radeon_bo_is_reserved(bo));

	if (!bo->tiling_flags)
		return 0;

	if (bo->surface_reg >= 0) {
		reg = &rdev->surface_regs[bo->surface_reg];
		i = bo->surface_reg;
		goto out;
	}

	steal = -1;
	for (i = 0; i < RADEON_GEM_MAX_SURFACES; i++) {

		reg = &rdev->surface_regs[i];
		if (!reg->bo)
			break;

		old_object = reg->bo;
		if (old_object->pin_count == 0)
			steal = i;
	}

	/* if we are all out */
	if (i == RADEON_GEM_MAX_SURFACES) {
		if (steal == -1)
			return -ENOMEM;
		/* find someone with a surface reg and nuke their BO */
		reg = &rdev->surface_regs[steal];
		old_object = reg->bo;
		/* blow away the mapping */
		DRM_DEBUG("stealing surface reg %d from %p\n", steal, old_object);
		ttm_bo_unmap_virtual(&old_object->tbo);
		old_object->surface_reg = -1;
		i = steal;
	}

	bo->surface_reg = i;
	reg->bo = bo;

out:
	radeon_set_surface_reg(rdev, i, bo->tiling_flags, bo->pitch,
			       bo->tbo.mem.start << PAGE_SHIFT,
			       bo->tbo.num_pages << PAGE_SHIFT);
	return 0;
}