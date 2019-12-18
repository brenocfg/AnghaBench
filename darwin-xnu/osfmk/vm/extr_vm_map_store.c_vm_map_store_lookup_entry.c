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
typedef  int /*<<< orphan*/  vm_map_offset_t ;
typedef  int /*<<< orphan*/  vm_map_entry_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_5__ {int /*<<< orphan*/  hdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  panic (char*) ; 
 scalar_t__ vm_map_store_has_RB_support (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vm_map_store_lookup_entry_ll (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vm_map_store_lookup_entry_rb (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

boolean_t
vm_map_store_lookup_entry(
	vm_map_t		map,
	vm_map_offset_t		address,
	vm_map_entry_t		*entry)		/* OUT */
{
#ifdef VM_MAP_STORE_USE_LL
	return (vm_map_store_lookup_entry_ll( map, address, entry ));
#elif defined VM_MAP_STORE_USE_RB
	if (vm_map_store_has_RB_support( &map->hdr )) {
		return (vm_map_store_lookup_entry_rb( map, address, entry ));
	} else {
		panic("VM map lookups need RB tree support.\n");
		return FALSE; /* For compiler warning.*/
	}
#endif
}