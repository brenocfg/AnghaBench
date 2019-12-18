#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vm_map_t ;
typedef  TYPE_2__* vm_map_entry_t ;
struct TYPE_13__ {scalar_t__ vme_start; struct TYPE_13__* vme_prev; } ;
struct TYPE_12__ {scalar_t__ holelistenabled; int /*<<< orphan*/  hdr; TYPE_2__* first_free; } ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  VM_MAP_ENTRY_DELETE ; 
 int /*<<< orphan*/  _vm_map_store_entry_unlink (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  update_first_free_ll (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  update_first_free_rb (TYPE_1__*,TYPE_2__*,scalar_t__) ; 
 scalar_t__ vm_map_store_has_RB_support (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vm_map_store_update (TYPE_1__*,TYPE_2__*,int /*<<< orphan*/ ) ; 

void
vm_map_store_entry_unlink( vm_map_t map, vm_map_entry_t entry)
{
	vm_map_t VMEU_map;
	vm_map_entry_t VMEU_entry = NULL;
	vm_map_entry_t VMEU_first_free = NULL;
	VMEU_map = (map);
	VMEU_entry = (entry);

	if (map->holelistenabled == FALSE) {
		if (VMEU_entry->vme_start <= VMEU_map->first_free->vme_start){
			VMEU_first_free = VMEU_entry->vme_prev;
		} else	{
			VMEU_first_free = VMEU_map->first_free;
		}
	}
	_vm_map_store_entry_unlink(&VMEU_map->hdr, VMEU_entry);
	vm_map_store_update( map, entry, VM_MAP_ENTRY_DELETE);
	update_first_free_ll(VMEU_map, VMEU_first_free);
#ifdef VM_MAP_STORE_USE_RB
	if (vm_map_store_has_RB_support( &VMEU_map->hdr )) {
		update_first_free_rb(VMEU_map, entry, FALSE);
	}
#endif
}