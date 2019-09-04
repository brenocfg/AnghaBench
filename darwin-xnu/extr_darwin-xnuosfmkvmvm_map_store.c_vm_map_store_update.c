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
typedef  void* vm_map_entry_t ;
struct TYPE_4__ {void* hint; void* first_free; int /*<<< orphan*/  holelistenabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
#define  VM_MAP_ENTRY_CREATE 129 
#define  VM_MAP_ENTRY_DELETE 128 
 void* vm_map_to_entry (TYPE_1__*) ; 

void
vm_map_store_update( vm_map_t map, vm_map_entry_t entry, int update_type )
{
	switch (update_type) {
		case VM_MAP_ENTRY_CREATE:
			break;
		case VM_MAP_ENTRY_DELETE:
			if((map->holelistenabled == FALSE) && ((entry) == (map)->first_free)) {
				(map)->first_free = vm_map_to_entry(map);
			}
			if((entry) == (map)->hint) {
				(map)->hint = vm_map_to_entry(map);
			}
			break;
		default:
			break;
	}
}