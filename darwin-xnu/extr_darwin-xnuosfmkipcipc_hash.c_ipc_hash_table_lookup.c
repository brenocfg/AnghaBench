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
typedef  int /*<<< orphan*/  mach_port_name_t ;
typedef  size_t mach_port_index_t ;
typedef  scalar_t__ ipc_object_t ;
typedef  TYPE_1__* ipc_entry_t ;
typedef  size_t ipc_entry_num_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_4__ {size_t ie_index; scalar_t__ ie_object; int /*<<< orphan*/  ie_bits; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IE_BITS_GEN (int /*<<< orphan*/ ) ; 
 size_t IH_TABLE_HASH (scalar_t__,size_t) ; 
 scalar_t__ IO_NULL ; 
 int /*<<< orphan*/  MACH_PORT_MAKE (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  assert (int) ; 

boolean_t
ipc_hash_table_lookup(
	ipc_entry_t		table,
	ipc_entry_num_t		size,
	ipc_object_t		obj,
	mach_port_name_t	*namep,
	ipc_entry_t		*entryp)
{
	mach_port_index_t hindex, index;

	if (obj == IO_NULL) {
		return FALSE;
	}

	hindex = IH_TABLE_HASH(obj, size);

	/*
	 *	Ideally, table[hindex].ie_index is the name we want.
	 *	However, must check ie_object to verify this,
	 *	because collisions can happen.  In case of a collision,
	 *	search farther along in the clump.
	 */

	while ((index = table[hindex].ie_index) != 0) {
		ipc_entry_t entry;

		assert(index < size);
		entry = &table[index];
		if (entry->ie_object == obj) {
			*entryp = entry;
			*namep = MACH_PORT_MAKE(index,
						IE_BITS_GEN(entry->ie_bits));
			return TRUE;
		}

		if (++hindex == size)
			hindex = 0;
	}

	return FALSE;
}