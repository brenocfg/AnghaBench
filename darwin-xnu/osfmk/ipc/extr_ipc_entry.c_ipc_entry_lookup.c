#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mach_port_name_t ;
typedef  size_t mach_port_index_t ;
typedef  TYPE_1__* ipc_space_t ;
typedef  TYPE_2__* ipc_entry_t ;
struct TYPE_8__ {int /*<<< orphan*/  ie_bits; } ;
struct TYPE_7__ {size_t is_table_size; TYPE_2__* is_table; } ;

/* Variables and functions */
 scalar_t__ IE_BITS_GEN (int /*<<< orphan*/ ) ; 
 scalar_t__ IE_BITS_TYPE (int /*<<< orphan*/ ) ; 
 TYPE_2__* IE_NULL ; 
 scalar_t__ MACH_PORT_GEN (int /*<<< orphan*/ ) ; 
 size_t MACH_PORT_INDEX (int /*<<< orphan*/ ) ; 
 scalar_t__ MACH_PORT_TYPE_NONE ; 
 int /*<<< orphan*/  assert (int) ; 
 int is_active (TYPE_1__*) ; 

ipc_entry_t
ipc_entry_lookup(
	ipc_space_t		space,
	mach_port_name_t	name)
{
	mach_port_index_t index;
	ipc_entry_t entry;

	assert(is_active(space));

	index = MACH_PORT_INDEX(name);
	if (index <  space->is_table_size) {
                entry = &space->is_table[index];
		if (IE_BITS_GEN(entry->ie_bits) != MACH_PORT_GEN(name) ||
		    IE_BITS_TYPE(entry->ie_bits) == MACH_PORT_TYPE_NONE) {
			entry = IE_NULL;		
		}
	}
	else {
		entry = IE_NULL;
	}

	assert((entry == IE_NULL) || IE_BITS_TYPE(entry->ie_bits));
	return entry;
}