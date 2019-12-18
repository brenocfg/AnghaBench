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
struct ttm_placement {scalar_t__ lpfn; scalar_t__ fpfn; int /*<<< orphan*/ * placement; } ;
struct TYPE_2__ {scalar_t__ mem_type; int /*<<< orphan*/  placement; } ;
struct ttm_buffer_object {scalar_t__ num_pages; int /*<<< orphan*/ * ttm; TYPE_1__ mem; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EINVAL ; 
 int /*<<< orphan*/  TTM_PL_MASK_MEMTYPE ; 
 scalar_t__ TTM_PL_SYSTEM ; 
 int ttm_bo_add_ttm (struct ttm_buffer_object*,int) ; 
 int /*<<< orphan*/  ttm_bo_is_reserved (struct ttm_buffer_object*) ; 
 int ttm_bo_mem_compat (struct ttm_placement*,TYPE_1__*) ; 
 int ttm_bo_move_buffer (struct ttm_buffer_object*,struct ttm_placement*,int,int) ; 
 int /*<<< orphan*/  ttm_flag_masked (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int ttm_bo_validate(struct ttm_buffer_object *bo,
			struct ttm_placement *placement,
			bool interruptible,
			bool no_wait_gpu)
{
	int ret;

	BUG_ON(!ttm_bo_is_reserved(bo));
	/* Check that range is valid */
	if (placement->lpfn || placement->fpfn)
		if (placement->fpfn > placement->lpfn ||
			(placement->lpfn - placement->fpfn) < bo->num_pages)
			return -EINVAL;
	/*
	 * Check whether we need to move buffer.
	 */
	ret = ttm_bo_mem_compat(placement, &bo->mem);
	if (ret < 0) {
		ret = ttm_bo_move_buffer(bo, placement, interruptible,
					 no_wait_gpu);
		if (ret)
			return ret;
	} else {
		/*
		 * Use the access and other non-mapping-related flag bits from
		 * the compatible memory placement flags to the active flags
		 */
		ttm_flag_masked(&bo->mem.placement, placement->placement[ret],
				~TTM_PL_MASK_MEMTYPE);
	}
	/*
	 * We might need to add a TTM.
	 */
	if (bo->mem.mem_type == TTM_PL_SYSTEM && bo->ttm == NULL) {
		ret = ttm_bo_add_ttm(bo, true);
		if (ret)
			return ret;
	}
	return 0;
}