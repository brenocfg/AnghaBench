#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vm_map_t ;
struct TYPE_4__ {scalar_t__ res_count; scalar_t__ map_refcnt; int /*<<< orphan*/  s_lock; } ;

/* Variables and functions */
 TYPE_1__* VM_MAP_NULL ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 

void
vm_map_reference(
	vm_map_t	map)
{
	if (map == VM_MAP_NULL)
		return;

	lck_mtx_lock(&map->s_lock);
#if	TASK_SWAPPER
	assert(map->res_count > 0);
	assert(map->map_refcnt >= map->res_count);
	map->res_count++;
#endif
	map->map_refcnt++;
	lck_mtx_unlock(&map->s_lock);
}