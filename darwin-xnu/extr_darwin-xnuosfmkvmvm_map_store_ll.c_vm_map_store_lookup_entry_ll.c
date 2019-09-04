#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vm_map_t ;
typedef  scalar_t__ vm_map_offset_t ;
typedef  TYPE_2__* vm_map_entry_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_12__ {scalar_t__ vme_start; scalar_t__ vme_end; struct TYPE_12__* vme_prev; struct TYPE_12__* vme_next; } ;
struct TYPE_11__ {TYPE_2__* hint; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SAVE_HINT_MAP_READ (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_2__* vm_map_first_entry (TYPE_1__*) ; 
 TYPE_2__* vm_map_to_entry (TYPE_1__*) ; 

boolean_t
vm_map_store_lookup_entry_ll(
	vm_map_t		map,
	vm_map_offset_t		address,
	vm_map_entry_t		*entry)		/* OUT */
{
	vm_map_entry_t		cur;
	vm_map_entry_t		last;

	/*
	 *	Start looking either from the head of the
	 *	list, or from the hint.
	 */
	cur = map->hint;

	if (cur == vm_map_to_entry(map))
		cur = cur->vme_next;

	if (address >= cur->vme_start) {
		/*
		 *	Go from hint to end of list.
		 *
		 *	But first, make a quick check to see if
		 *	we are already looking at the entry we
		 *	want (which is usually the case).
		 *	Note also that we don't need to save the hint
		 *	here... it is the same hint (unless we are
		 *	at the header, in which case the hint didn't
		 *	buy us anything anyway).
		 */
		last = vm_map_to_entry(map);
		if ((cur != last) && (cur->vme_end > address)) {
			*entry = cur;
			return(TRUE);
		}
	}
	else {
		/*
		 *	Go from start to hint, *inclusively*
		 */
		last = cur->vme_next;
		cur = vm_map_first_entry(map);
	}

	/*
	 *	Search linearly
	 */

	while (cur != last) {
		if (cur->vme_end > address) {
			if (address >= cur->vme_start) {
				/*
				 *	Save this lookup for future
				 *	hints, and return
				 */

				*entry = cur;
				SAVE_HINT_MAP_READ(map, cur);

				return(TRUE);
			}
			break;
		}
		cur = cur->vme_next;
	}
	*entry = cur->vme_prev;
	SAVE_HINT_MAP_READ(map, *entry);

	return(FALSE);
}