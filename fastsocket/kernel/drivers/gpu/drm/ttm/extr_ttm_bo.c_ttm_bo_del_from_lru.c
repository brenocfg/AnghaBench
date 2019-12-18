#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct ttm_buffer_object {int /*<<< orphan*/  lru; int /*<<< orphan*/  swap; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 

int ttm_bo_del_from_lru(struct ttm_buffer_object *bo)
{
	int put_count = 0;

	if (!list_empty(&bo->swap)) {
		list_del_init(&bo->swap);
		++put_count;
	}
	if (!list_empty(&bo->lru)) {
		list_del_init(&bo->lru);
		++put_count;
	}

	/*
	 * TODO: Add a driver hook to delete from
	 * driver-specific LRU's here.
	 */

	return put_count;
}