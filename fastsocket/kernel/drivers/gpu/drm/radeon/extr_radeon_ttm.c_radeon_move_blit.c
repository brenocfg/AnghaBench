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
typedef  int uint64_t ;
struct ttm_mem_reg {int start; int mem_type; int num_pages; } ;
struct ttm_buffer_object {struct radeon_fence* sync_obj; int /*<<< orphan*/  bdev; } ;
struct radeon_fence {int dummy; } ;
struct TYPE_3__ {int vram_start; int gtt_start; } ;
struct radeon_device {TYPE_2__* ring; TYPE_1__ mc; } ;
struct TYPE_4__ {int /*<<< orphan*/  ready; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,...) ; 
 int EINVAL ; 
 int PAGE_SHIFT ; 
 int PAGE_SIZE ; 
 int RADEON_GPU_PAGE_SIZE ; 
#define  TTM_PL_TT 129 
#define  TTM_PL_VRAM 128 
 int radeon_copy (struct radeon_device*,int,int,int,struct radeon_fence**) ; 
 int radeon_copy_ring_index (struct radeon_device*) ; 
 int /*<<< orphan*/  radeon_fence_unref (struct radeon_fence**) ; 
 struct radeon_device* radeon_get_rdev (int /*<<< orphan*/ ) ; 
 int ttm_bo_move_accel_cleanup (struct ttm_buffer_object*,void*,int,int,struct ttm_mem_reg*) ; 

__attribute__((used)) static int radeon_move_blit(struct ttm_buffer_object *bo,
			bool evict, bool no_wait_gpu,
			struct ttm_mem_reg *new_mem,
			struct ttm_mem_reg *old_mem)
{
	struct radeon_device *rdev;
	uint64_t old_start, new_start;
	struct radeon_fence *fence;
	int r, ridx;

	rdev = radeon_get_rdev(bo->bdev);
	ridx = radeon_copy_ring_index(rdev);
	old_start = old_mem->start << PAGE_SHIFT;
	new_start = new_mem->start << PAGE_SHIFT;

	switch (old_mem->mem_type) {
	case TTM_PL_VRAM:
		old_start += rdev->mc.vram_start;
		break;
	case TTM_PL_TT:
		old_start += rdev->mc.gtt_start;
		break;
	default:
		DRM_ERROR("Unknown placement %d\n", old_mem->mem_type);
		return -EINVAL;
	}
	switch (new_mem->mem_type) {
	case TTM_PL_VRAM:
		new_start += rdev->mc.vram_start;
		break;
	case TTM_PL_TT:
		new_start += rdev->mc.gtt_start;
		break;
	default:
		DRM_ERROR("Unknown placement %d\n", old_mem->mem_type);
		return -EINVAL;
	}
	if (!rdev->ring[ridx].ready) {
		DRM_ERROR("Trying to move memory with ring turned off.\n");
		return -EINVAL;
	}

	BUILD_BUG_ON((PAGE_SIZE % RADEON_GPU_PAGE_SIZE) != 0);

	/* sync other rings */
	fence = bo->sync_obj;
	r = radeon_copy(rdev, old_start, new_start,
			new_mem->num_pages * (PAGE_SIZE / RADEON_GPU_PAGE_SIZE), /* GPU pages */
			&fence);
	/* FIXME: handle copy error */
	r = ttm_bo_move_accel_cleanup(bo, (void *)fence,
				      evict, no_wait_gpu, new_mem);
	radeon_fence_unref(&fence);
	return r;
}