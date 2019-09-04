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
typedef  int /*<<< orphan*/  vm_map_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  TYPE_1__* task_t ;
struct TYPE_4__ {int /*<<< orphan*/  map; } ;

/* Variables and functions */
 scalar_t__ get_map_nentries (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kernel_map ; 
 TYPE_1__* kernel_task ; 

uint64_t get_task_memory_region_count(task_t task)
{
	vm_map_t map;
	map = (task == kernel_task) ? kernel_map: task->map;
	return((uint64_t)get_map_nentries(map));
}