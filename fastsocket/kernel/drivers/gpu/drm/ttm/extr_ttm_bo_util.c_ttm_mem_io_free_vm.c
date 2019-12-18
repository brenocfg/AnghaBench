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
struct TYPE_2__ {int io_reserved_vm; } ;
struct ttm_mem_reg {TYPE_1__ bus; } ;
struct ttm_buffer_object {int /*<<< orphan*/  bdev; int /*<<< orphan*/  io_reserve_lru; struct ttm_mem_reg mem; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ttm_mem_io_free (int /*<<< orphan*/ ,struct ttm_mem_reg*) ; 

void ttm_mem_io_free_vm(struct ttm_buffer_object *bo)
{
	struct ttm_mem_reg *mem = &bo->mem;

	if (mem->bus.io_reserved_vm) {
		mem->bus.io_reserved_vm = false;
		list_del_init(&bo->io_reserve_lru);
		ttm_mem_io_free(bo->bdev, mem);
	}
}