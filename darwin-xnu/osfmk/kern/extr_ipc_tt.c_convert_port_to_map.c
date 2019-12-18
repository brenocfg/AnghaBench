#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vm_map_t ;
typedef  TYPE_1__* task_t ;
typedef  int /*<<< orphan*/  ipc_port_t ;
struct TYPE_5__ {int /*<<< orphan*/  map; int /*<<< orphan*/  active; } ;

/* Variables and functions */
 TYPE_1__* TASK_NULL ; 
 int /*<<< orphan*/  VM_MAP_NULL ; 
 TYPE_1__* convert_port_to_locked_task (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  task_unlock (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_map_reference_swap (int /*<<< orphan*/ ) ; 

vm_map_t
convert_port_to_map(
	ipc_port_t	port)
{
	task_t task;
	vm_map_t map;

	task = convert_port_to_locked_task(port);
		
	if (task == TASK_NULL)
		return VM_MAP_NULL;

	if (!task->active) {
		task_unlock(task);
		return VM_MAP_NULL;
	}
		
	map = task->map;
	vm_map_reference_swap(map);
	task_unlock(task);
	return map;
}