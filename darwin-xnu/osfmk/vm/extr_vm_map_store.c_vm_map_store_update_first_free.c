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
typedef  TYPE_1__* vm_map_t ;
typedef  int /*<<< orphan*/  vm_map_entry_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_5__ {int /*<<< orphan*/  hdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  update_first_free_ll (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_first_free_rb (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ vm_map_store_has_RB_support (int /*<<< orphan*/ *) ; 

void
vm_map_store_update_first_free( vm_map_t map, vm_map_entry_t first_free_entry, boolean_t new_entry_creation)
{
	update_first_free_ll(map, first_free_entry);
#ifdef VM_MAP_STORE_USE_RB
	if (vm_map_store_has_RB_support( &map->hdr )) {
		update_first_free_rb(map, first_free_entry, new_entry_creation);
	}
#endif
}