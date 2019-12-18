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
typedef  int /*<<< orphan*/  vm_map_offset_t ;
typedef  TYPE_1__* vm_map_entry_t ;
struct TYPE_4__ {struct TYPE_4__* vme_next; } ;

/* Variables and functions */
 int /*<<< orphan*/  c_vm_map_simplify_called ; 
 int /*<<< orphan*/  counter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_map_lock (int /*<<< orphan*/ ) ; 
 scalar_t__ vm_map_lookup_entry (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__**) ; 
 int /*<<< orphan*/  vm_map_simplify_entry (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  vm_map_unlock (int /*<<< orphan*/ ) ; 

void
vm_map_simplify(
	vm_map_t	map,
	vm_map_offset_t	start)
{
	vm_map_entry_t	this_entry;

	vm_map_lock(map);
	if (vm_map_lookup_entry(map, start, &this_entry)) {
		vm_map_simplify_entry(map, this_entry);
		vm_map_simplify_entry(map, this_entry->vme_next);
	}
	counter(c_vm_map_simplify_called++);
	vm_map_unlock(map);
}