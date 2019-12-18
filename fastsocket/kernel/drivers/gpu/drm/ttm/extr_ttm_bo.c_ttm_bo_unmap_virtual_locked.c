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
struct TYPE_2__ {scalar_t__ num_pages; } ;
struct ttm_buffer_object {TYPE_1__ mem; scalar_t__ addr_space_offset; struct ttm_bo_device* bdev; } ;
struct ttm_bo_device {int /*<<< orphan*/  dev_mapping; } ;
typedef  int loff_t ;

/* Variables and functions */
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  ttm_mem_io_free_vm (struct ttm_buffer_object*) ; 
 int /*<<< orphan*/  unmap_mapping_range (int /*<<< orphan*/ ,int,int,int) ; 

void ttm_bo_unmap_virtual_locked(struct ttm_buffer_object *bo)
{
	struct ttm_bo_device *bdev = bo->bdev;
	loff_t offset = (loff_t) bo->addr_space_offset;
	loff_t holelen = ((loff_t) bo->mem.num_pages) << PAGE_SHIFT;

	if (!bdev->dev_mapping)
		return;
	unmap_mapping_range(bdev->dev_mapping, offset, holelen, 1);
	ttm_mem_io_free_vm(bo);
}