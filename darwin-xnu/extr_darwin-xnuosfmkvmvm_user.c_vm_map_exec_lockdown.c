#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vm_map_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
struct TYPE_6__ {int /*<<< orphan*/  map_disallow_new_exec; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_INVALID_ARGUMENT ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_1__* VM_MAP_NULL ; 
 int /*<<< orphan*/  vm_map_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_map_unlock (TYPE_1__*) ; 

kern_return_t
vm_map_exec_lockdown(
	vm_map_t 	map)
{
	if (map == VM_MAP_NULL)
		return(KERN_INVALID_ARGUMENT);

	vm_map_lock(map);
	map->map_disallow_new_exec = TRUE;
	vm_map_unlock(map);

	return(KERN_SUCCESS);
}