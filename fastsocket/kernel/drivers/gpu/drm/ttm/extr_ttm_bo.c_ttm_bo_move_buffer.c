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
struct ttm_placement {int dummy; } ;
struct TYPE_4__ {int io_reserved_vm; scalar_t__ io_reserved_count; } ;
struct ttm_mem_reg {int num_pages; int size; scalar_t__ mm_node; TYPE_2__ bus; int /*<<< orphan*/  page_alignment; } ;
struct TYPE_3__ {int /*<<< orphan*/  page_alignment; } ;
struct ttm_buffer_object {int num_pages; TYPE_1__ mem; struct ttm_bo_device* bdev; } ;
struct ttm_bo_device {int /*<<< orphan*/  fence_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int ttm_bo_handle_move_mem (struct ttm_buffer_object*,struct ttm_mem_reg*,int,int,int) ; 
 int /*<<< orphan*/  ttm_bo_is_reserved (struct ttm_buffer_object*) ; 
 int /*<<< orphan*/  ttm_bo_mem_put (struct ttm_buffer_object*,struct ttm_mem_reg*) ; 
 int ttm_bo_mem_space (struct ttm_buffer_object*,struct ttm_placement*,struct ttm_mem_reg*,int,int) ; 
 int ttm_bo_wait (struct ttm_buffer_object*,int,int,int) ; 

int ttm_bo_move_buffer(struct ttm_buffer_object *bo,
			struct ttm_placement *placement,
			bool interruptible,
			bool no_wait_gpu)
{
	int ret = 0;
	struct ttm_mem_reg mem;
	struct ttm_bo_device *bdev = bo->bdev;

	BUG_ON(!ttm_bo_is_reserved(bo));

	/*
	 * FIXME: It's possible to pipeline buffer moves.
	 * Have the driver move function wait for idle when necessary,
	 * instead of doing it here.
	 */
	spin_lock(&bdev->fence_lock);
	ret = ttm_bo_wait(bo, false, interruptible, no_wait_gpu);
	spin_unlock(&bdev->fence_lock);
	if (ret)
		return ret;
	mem.num_pages = bo->num_pages;
	mem.size = mem.num_pages << PAGE_SHIFT;
	mem.page_alignment = bo->mem.page_alignment;
	mem.bus.io_reserved_vm = false;
	mem.bus.io_reserved_count = 0;
	/*
	 * Determine where to move the buffer.
	 */
	ret = ttm_bo_mem_space(bo, placement, &mem,
			       interruptible, no_wait_gpu);
	if (ret)
		goto out_unlock;
	ret = ttm_bo_handle_move_mem(bo, &mem, false,
				     interruptible, no_wait_gpu);
out_unlock:
	if (ret && mem.mm_node)
		ttm_bo_mem_put(bo, &mem);
	return ret;
}