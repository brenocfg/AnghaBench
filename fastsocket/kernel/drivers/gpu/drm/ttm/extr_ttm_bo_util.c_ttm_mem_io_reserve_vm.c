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
struct ttm_mem_type_manager {int /*<<< orphan*/  io_reserve_lru; scalar_t__ use_io_reserve_lru; } ;
struct TYPE_3__ {int io_reserved_vm; } ;
struct ttm_mem_reg {size_t mem_type; TYPE_1__ bus; } ;
struct ttm_buffer_object {int /*<<< orphan*/  io_reserve_lru; TYPE_2__* bdev; struct ttm_mem_reg mem; } ;
struct TYPE_4__ {struct ttm_mem_type_manager* man; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int ttm_mem_io_reserve (TYPE_2__*,struct ttm_mem_reg*) ; 
 scalar_t__ unlikely (int) ; 

int ttm_mem_io_reserve_vm(struct ttm_buffer_object *bo)
{
	struct ttm_mem_reg *mem = &bo->mem;
	int ret;

	if (!mem->bus.io_reserved_vm) {
		struct ttm_mem_type_manager *man =
			&bo->bdev->man[mem->mem_type];

		ret = ttm_mem_io_reserve(bo->bdev, mem);
		if (unlikely(ret != 0))
			return ret;
		mem->bus.io_reserved_vm = true;
		if (man->use_io_reserve_lru)
			list_add_tail(&bo->io_reserve_lru,
				      &man->io_reserve_lru);
	}
	return 0;
}