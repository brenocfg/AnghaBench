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
typedef  scalar_t__ mach_port_type_t ;
typedef  int /*<<< orphan*/  mach_port_name_t ;
typedef  size_t mach_port_index_t ;
typedef  TYPE_1__* ipc_space_t ;
typedef  TYPE_2__* ipc_entry_t ;
typedef  size_t ipc_entry_num_t ;
struct TYPE_12__ {int /*<<< orphan*/  ie_bits; } ;
struct TYPE_11__ {size_t is_table_size; TYPE_2__* is_table; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IE_BITS_GEN (int /*<<< orphan*/ ) ; 
 scalar_t__ IE_BITS_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MACH_PORT_MAKE (size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ MACH_PORT_TYPE_NONE ; 
 int /*<<< orphan*/  ipc_right_destroy (TYPE_1__*,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_active (TYPE_1__*) ; 
 scalar_t__ is_growing (TYPE_1__*) ; 
 int /*<<< orphan*/  is_write_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  is_write_sleep (TYPE_1__*) ; 
 int /*<<< orphan*/  is_write_unlock (TYPE_1__*) ; 

void
ipc_space_clean(
	ipc_space_t space)
{
	ipc_entry_t table;
	ipc_entry_num_t size;
	mach_port_index_t index;

	/*
	 *	If somebody is trying to grow the table,
	 *	we must wait until they finish and figure
	 *	out the space died.
	 */
 retry:
	is_write_lock(space);
	while (is_growing(space))
		is_write_sleep(space);

	if (!is_active(space)) {
		is_write_unlock(space);
		return;
	}

	/*
	 *	Now we can futz with it	since we have the write lock.
	 */

	table = space->is_table;
	size = space->is_table_size;

	for (index = 0; index < size; index++) {
		ipc_entry_t entry = &table[index];
		mach_port_type_t type;

		type = IE_BITS_TYPE(entry->ie_bits);
		if (type != MACH_PORT_TYPE_NONE) {
			mach_port_name_t name =	MACH_PORT_MAKE(index,
						IE_BITS_GEN(entry->ie_bits));
			ipc_right_destroy(space, name, entry, FALSE, 0); /* unlocks space */
			goto retry;
		}
	}

        /*
	 * JMM - Now the table is cleaned out.  We don't bother shrinking the
	 * size of the table at this point, but we probably should if it is
	 * really large.
	 */
	
	is_write_unlock(space);
}