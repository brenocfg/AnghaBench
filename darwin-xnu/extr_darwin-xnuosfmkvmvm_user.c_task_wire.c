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
typedef  scalar_t__ boolean_t ;
struct TYPE_6__ {int wiring_required; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_INVALID_ARGUMENT ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 scalar_t__ TRUE ; 
 TYPE_1__* VM_MAP_NULL ; 
 int /*<<< orphan*/  vm_map_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_map_unlock (TYPE_1__*) ; 

kern_return_t
task_wire(
	vm_map_t	map,
	boolean_t	must_wire)
{
	if (map == VM_MAP_NULL)
		return(KERN_INVALID_ARGUMENT);

	vm_map_lock(map);
	map->wiring_required = (must_wire == TRUE);
	vm_map_unlock(map);

	return(KERN_SUCCESS);
}