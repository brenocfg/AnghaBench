#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vm_map_t ;
typedef  int uint64_t ;
typedef  TYPE_2__* task_t ;
struct TYPE_7__ {TYPE_1__* map; } ;
struct TYPE_6__ {int /*<<< orphan*/  pmap; } ;

/* Variables and functions */
 int PAGE_SIZE_64 ; 
 TYPE_1__* kernel_map ; 
 TYPE_2__* kernel_task ; 
 scalar_t__ pmap_resident_count (int /*<<< orphan*/ ) ; 

uint64_t get_task_resident_size(task_t task) 
{
	vm_map_t map;
	
	map = (task == kernel_task) ? kernel_map: task->map;
	return((uint64_t)pmap_resident_count(map->pmap) * PAGE_SIZE_64);
}