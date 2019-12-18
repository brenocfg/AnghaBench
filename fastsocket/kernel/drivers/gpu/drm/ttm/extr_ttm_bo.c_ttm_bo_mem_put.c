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
struct ttm_mem_type_manager {TYPE_2__* func; } ;
struct ttm_mem_reg {size_t mem_type; scalar_t__ mm_node; } ;
struct ttm_buffer_object {TYPE_1__* bdev; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* put_node ) (struct ttm_mem_type_manager*,struct ttm_mem_reg*) ;} ;
struct TYPE_3__ {struct ttm_mem_type_manager* man; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct ttm_mem_type_manager*,struct ttm_mem_reg*) ; 

void ttm_bo_mem_put(struct ttm_buffer_object *bo, struct ttm_mem_reg *mem)
{
	struct ttm_mem_type_manager *man = &bo->bdev->man[mem->mem_type];

	if (mem->mm_node)
		(*man->func->put_node)(man, mem);
}