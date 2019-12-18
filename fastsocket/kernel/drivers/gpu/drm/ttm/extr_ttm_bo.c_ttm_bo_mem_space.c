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
typedef  size_t uint32_t ;
struct ttm_placement {int num_placement; int num_busy_placement; int /*<<< orphan*/ * busy_placement; int /*<<< orphan*/ * placement; } ;
struct ttm_mem_type_manager {scalar_t__ has_type; TYPE_1__* func; scalar_t__ use_type; } ;
struct ttm_mem_reg {size_t mem_type; size_t placement; int /*<<< orphan*/ * mm_node; } ;
struct TYPE_4__ {int /*<<< orphan*/  placement; } ;
struct ttm_buffer_object {TYPE_2__ mem; struct ttm_bo_device* bdev; } ;
struct ttm_bo_device {struct ttm_mem_type_manager* man; } ;
struct TYPE_3__ {int (* get_node ) (struct ttm_mem_type_manager*,struct ttm_buffer_object*,struct ttm_placement*,struct ttm_mem_reg*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int ERESTARTSYS ; 
 int /*<<< orphan*/  TTM_PL_MASK_MEMTYPE ; 
 size_t TTM_PL_SYSTEM ; 
 int stub1 (struct ttm_mem_type_manager*,struct ttm_buffer_object*,struct ttm_placement*,struct ttm_mem_reg*) ; 
 int ttm_bo_mem_force_space (struct ttm_buffer_object*,size_t,struct ttm_placement*,struct ttm_mem_reg*,int,int) ; 
 int ttm_bo_mt_compatible (struct ttm_mem_type_manager*,size_t,int /*<<< orphan*/ ,size_t*) ; 
 size_t ttm_bo_select_caching (struct ttm_mem_type_manager*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  ttm_flag_masked (size_t*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ttm_mem_type_from_flags (int /*<<< orphan*/ ,size_t*) ; 
 scalar_t__ unlikely (int) ; 

int ttm_bo_mem_space(struct ttm_buffer_object *bo,
			struct ttm_placement *placement,
			struct ttm_mem_reg *mem,
			bool interruptible,
			bool no_wait_gpu)
{
	struct ttm_bo_device *bdev = bo->bdev;
	struct ttm_mem_type_manager *man;
	uint32_t mem_type = TTM_PL_SYSTEM;
	uint32_t cur_flags = 0;
	bool type_found = false;
	bool type_ok = false;
	bool has_erestartsys = false;
	int i, ret;

	mem->mm_node = NULL;
	for (i = 0; i < placement->num_placement; ++i) {
		ret = ttm_mem_type_from_flags(placement->placement[i],
						&mem_type);
		if (ret)
			return ret;
		man = &bdev->man[mem_type];

		type_ok = ttm_bo_mt_compatible(man,
						mem_type,
						placement->placement[i],
						&cur_flags);

		if (!type_ok)
			continue;

		cur_flags = ttm_bo_select_caching(man, bo->mem.placement,
						  cur_flags);
		/*
		 * Use the access and other non-mapping-related flag bits from
		 * the memory placement flags to the current flags
		 */
		ttm_flag_masked(&cur_flags, placement->placement[i],
				~TTM_PL_MASK_MEMTYPE);

		if (mem_type == TTM_PL_SYSTEM)
			break;

		if (man->has_type && man->use_type) {
			type_found = true;
			ret = (*man->func->get_node)(man, bo, placement, mem);
			if (unlikely(ret))
				return ret;
		}
		if (mem->mm_node)
			break;
	}

	if ((type_ok && (mem_type == TTM_PL_SYSTEM)) || mem->mm_node) {
		mem->mem_type = mem_type;
		mem->placement = cur_flags;
		return 0;
	}

	if (!type_found)
		return -EINVAL;

	for (i = 0; i < placement->num_busy_placement; ++i) {
		ret = ttm_mem_type_from_flags(placement->busy_placement[i],
						&mem_type);
		if (ret)
			return ret;
		man = &bdev->man[mem_type];
		if (!man->has_type)
			continue;
		if (!ttm_bo_mt_compatible(man,
						mem_type,
						placement->busy_placement[i],
						&cur_flags))
			continue;

		cur_flags = ttm_bo_select_caching(man, bo->mem.placement,
						  cur_flags);
		/*
		 * Use the access and other non-mapping-related flag bits from
		 * the memory placement flags to the current flags
		 */
		ttm_flag_masked(&cur_flags, placement->busy_placement[i],
				~TTM_PL_MASK_MEMTYPE);


		if (mem_type == TTM_PL_SYSTEM) {
			mem->mem_type = mem_type;
			mem->placement = cur_flags;
			mem->mm_node = NULL;
			return 0;
		}

		ret = ttm_bo_mem_force_space(bo, mem_type, placement, mem,
						interruptible, no_wait_gpu);
		if (ret == 0 && mem->mm_node) {
			mem->placement = cur_flags;
			return 0;
		}
		if (ret == -ERESTARTSYS)
			has_erestartsys = true;
	}
	ret = (has_erestartsys) ? -ERESTARTSYS : -ENOMEM;
	return ret;
}