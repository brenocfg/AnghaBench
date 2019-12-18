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
typedef  int vm_prot_t ;
typedef  int /*<<< orphan*/  vm_map_t ;
typedef  scalar_t__ vm_map_offset_t ;
typedef  TYPE_1__* vm_map_entry_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_4__ {scalar_t__ vme_start; int protection; scalar_t__ vme_end; struct TYPE_4__* vme_next; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  vm_map_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_map_lookup_entry (int /*<<< orphan*/ ,scalar_t__,TYPE_1__**) ; 
 scalar_t__ vm_map_max (int /*<<< orphan*/ ) ; 
 scalar_t__ vm_map_min (int /*<<< orphan*/ ) ; 
 TYPE_1__* vm_map_to_entry (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_map_unlock (int /*<<< orphan*/ ) ; 

boolean_t
vm_map_check_protection(vm_map_t map, vm_map_offset_t start,
			vm_map_offset_t end, vm_prot_t protection)
{
	vm_map_entry_t entry;
	vm_map_entry_t tmp_entry;

	vm_map_lock(map);

	if (start < vm_map_min(map) || end > vm_map_max(map) || start > end)
	{
		vm_map_unlock(map);
		return (FALSE);
	}

	if (!vm_map_lookup_entry(map, start, &tmp_entry)) {
		vm_map_unlock(map);
		return(FALSE);
	}

	entry = tmp_entry;

	while (start < end) {
		if (entry == vm_map_to_entry(map)) {
			vm_map_unlock(map);
			return(FALSE);
		}

		/*
		 *	No holes allowed!
		 */

		if (start < entry->vme_start) {
			vm_map_unlock(map);
			return(FALSE);
		}

		/*
		 * Check protection associated with entry.
		 */

		if ((entry->protection & protection) != protection) {
			vm_map_unlock(map);
			return(FALSE);
		}

		/* go to next entry */

		start = entry->vme_end;
		entry = entry->vme_next;
	}
	vm_map_unlock(map);
	return(TRUE);
}