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
typedef  int /*<<< orphan*/  mach_port_name_t ;
typedef  scalar_t__ mach_port_index_t ;
typedef  scalar_t__ mach_port_gen_t ;
typedef  scalar_t__ kern_return_t ;
typedef  TYPE_1__* ipc_space_t ;
typedef  TYPE_2__* ipc_entry_t ;
struct TYPE_12__ {scalar_t__ ie_next; scalar_t__ ie_object; int /*<<< orphan*/  ie_request; scalar_t__ ie_bits; } ;
struct TYPE_11__ {scalar_t__ is_table_size; int /*<<< orphan*/  is_table_free; TYPE_2__* is_table; } ;

/* Variables and functions */
 scalar_t__ IE_BITS_GEN (scalar_t__) ; 
 scalar_t__ IE_BITS_TYPE (scalar_t__) ; 
 int /*<<< orphan*/  IE_REQ_NONE ; 
 scalar_t__ IO_NULL ; 
 scalar_t__ KERN_FAILURE ; 
 scalar_t__ KERN_INVALID_TASK ; 
 scalar_t__ KERN_NO_SPACE ; 
 scalar_t__ KERN_SUCCESS ; 
 scalar_t__ MACH_PORT_GEN (int /*<<< orphan*/ ) ; 
 scalar_t__ MACH_PORT_INDEX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MACH_PORT_MAKE (scalar_t__,scalar_t__) ; 
 int MACH_PORT_VALID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ ipc_entry_grow_table (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  ipc_entry_modified (TYPE_1__*,int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ ipc_table_max_entries () ; 
 int /*<<< orphan*/  is_active (TYPE_1__*) ; 
 int /*<<< orphan*/  is_write_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  is_write_unlock (TYPE_1__*) ; 

kern_return_t
ipc_entry_alloc_name(
	ipc_space_t		space,
	mach_port_name_t	name,
	ipc_entry_t		*entryp)
{
	mach_port_index_t index = MACH_PORT_INDEX(name);
	mach_port_gen_t gen = MACH_PORT_GEN(name);

	if (index > ipc_table_max_entries())
		return KERN_NO_SPACE;

	assert(MACH_PORT_VALID(name));


	is_write_lock(space);

	for (;;) {
		ipc_entry_t entry;

		if (!is_active(space)) {
			is_write_unlock(space);
			return KERN_INVALID_TASK;
		}

		/*
		 *	If we are under the table cutoff,
		 *	there are usually four cases:
		 *		1) The entry is reserved (index 0)
		 *		2) The entry is inuse, for the same name
		 *		3) The entry is inuse, for a different name
		 *		4) The entry is free
		 *	For a task with a "fast" IPC space, we disallow
		 *	cases 1) and 3), because ports cannot be renamed.
		 */
		if (index < space->is_table_size) {
			ipc_entry_t table = space->is_table;

			entry = &table[index];

			if (index == 0) {
				/* case #1 - the entry is reserved */
				assert(!IE_BITS_TYPE(entry->ie_bits));
				assert(!IE_BITS_GEN(entry->ie_bits));
				is_write_unlock(space);				
				return KERN_FAILURE;
			} else if (IE_BITS_TYPE(entry->ie_bits)) {
				if (IE_BITS_GEN(entry->ie_bits) == gen) {
					/* case #2 -- the entry is inuse, for the same name */
					*entryp = entry;
					return KERN_SUCCESS;
				} else {
					/* case #3 -- the entry is inuse, for a different name. */
					/* Collisions are not allowed */
					is_write_unlock(space);					
					return KERN_FAILURE;
				}
			} else {
				mach_port_index_t free_index, next_index;

				/*
				 *      case #4 -- the entry is free
				 *	Rip the entry out of the free list.
				 */

				for (free_index = 0;
				     (next_index = table[free_index].ie_next)
							!= index;
				     free_index = next_index)
					continue;

				table[free_index].ie_next =
					table[next_index].ie_next;
				space->is_table_free--;

				/* mark the previous entry modified - reconstructing the name */
				ipc_entry_modified(space, 
						   MACH_PORT_MAKE(free_index, 
						   	IE_BITS_GEN(table[free_index].ie_bits)),
						   &table[free_index]);

				entry->ie_bits = gen;
				entry->ie_request = IE_REQ_NONE;
				*entryp = entry;

				assert(entry->ie_object == IO_NULL);
				return KERN_SUCCESS;
			}
		}

		/*
		 *      We grow the table so that the name
		 *	index fits in the array space.
		 *      Because the space will be unlocked,
		 *      we must restart.
		 */
                kern_return_t kr;
		kr = ipc_entry_grow_table(space, index + 1);
		assert(kr != KERN_NO_SPACE);
		if (kr != KERN_SUCCESS) {
			/* space is unlocked */
			return kr;
		}
		continue;
	}
}