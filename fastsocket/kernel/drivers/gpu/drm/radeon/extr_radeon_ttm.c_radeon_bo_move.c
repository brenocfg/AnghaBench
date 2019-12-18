#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ttm_mem_reg {scalar_t__ mem_type; } ;
struct ttm_buffer_object {int /*<<< orphan*/ * ttm; int /*<<< orphan*/  bdev; struct ttm_mem_reg mem; } ;
struct radeon_device {TYPE_3__* asic; TYPE_1__* ring; } ;
struct TYPE_5__ {int /*<<< orphan*/ * copy; } ;
struct TYPE_6__ {TYPE_2__ copy; } ;
struct TYPE_4__ {int /*<<< orphan*/  ready; } ;

/* Variables and functions */
 scalar_t__ TTM_PL_SYSTEM ; 
 scalar_t__ TTM_PL_TT ; 
 scalar_t__ TTM_PL_VRAM ; 
 size_t radeon_copy_ring_index (struct radeon_device*) ; 
 struct radeon_device* radeon_get_rdev (int /*<<< orphan*/ ) ; 
 int radeon_move_blit (struct ttm_buffer_object*,int,int,struct ttm_mem_reg*,struct ttm_mem_reg*) ; 
 int /*<<< orphan*/  radeon_move_null (struct ttm_buffer_object*,struct ttm_mem_reg*) ; 
 int radeon_move_ram_vram (struct ttm_buffer_object*,int,int,int,struct ttm_mem_reg*) ; 
 int radeon_move_vram_ram (struct ttm_buffer_object*,int,int,int,struct ttm_mem_reg*) ; 
 int ttm_bo_move_memcpy (struct ttm_buffer_object*,int,int,struct ttm_mem_reg*) ; 

__attribute__((used)) static int radeon_bo_move(struct ttm_buffer_object *bo,
			bool evict, bool interruptible,
			bool no_wait_gpu,
			struct ttm_mem_reg *new_mem)
{
	struct radeon_device *rdev;
	struct ttm_mem_reg *old_mem = &bo->mem;
	int r;

	rdev = radeon_get_rdev(bo->bdev);
	if (old_mem->mem_type == TTM_PL_SYSTEM && bo->ttm == NULL) {
		radeon_move_null(bo, new_mem);
		return 0;
	}
	if ((old_mem->mem_type == TTM_PL_TT &&
	     new_mem->mem_type == TTM_PL_SYSTEM) ||
	    (old_mem->mem_type == TTM_PL_SYSTEM &&
	     new_mem->mem_type == TTM_PL_TT)) {
		/* bind is enough */
		radeon_move_null(bo, new_mem);
		return 0;
	}
	if (!rdev->ring[radeon_copy_ring_index(rdev)].ready ||
	    rdev->asic->copy.copy == NULL) {
		/* use memcpy */
		goto memcpy;
	}

	if (old_mem->mem_type == TTM_PL_VRAM &&
	    new_mem->mem_type == TTM_PL_SYSTEM) {
		r = radeon_move_vram_ram(bo, evict, interruptible,
					no_wait_gpu, new_mem);
	} else if (old_mem->mem_type == TTM_PL_SYSTEM &&
		   new_mem->mem_type == TTM_PL_VRAM) {
		r = radeon_move_ram_vram(bo, evict, interruptible,
					    no_wait_gpu, new_mem);
	} else {
		r = radeon_move_blit(bo, evict, no_wait_gpu, new_mem, old_mem);
	}

	if (r) {
memcpy:
		r = ttm_bo_move_memcpy(bo, evict, no_wait_gpu, new_mem);
	}
	return r;
}