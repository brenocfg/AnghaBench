#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mach_port_name_t ;
typedef  size_t mach_port_index_t ;
typedef  int /*<<< orphan*/  mach_port_gen_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  TYPE_1__* ipc_space_t ;
typedef  TYPE_2__* ipc_entry_t ;
typedef  int /*<<< orphan*/  ipc_entry_bits_t ;
struct TYPE_7__ {size_t ie_next; int /*<<< orphan*/  ie_request; int /*<<< orphan*/  ie_bits; } ;
struct TYPE_6__ {scalar_t__ is_table_size; int /*<<< orphan*/  is_table_free; TYPE_2__* is_table; } ;

/* Variables and functions */
 int /*<<< orphan*/  IE_REQ_NONE ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int /*<<< orphan*/  MACH_PORT_MAKE (size_t,int /*<<< orphan*/ ) ; 
 int MACH_PORT_VALID (int /*<<< orphan*/ ) ; 
 scalar_t__ __improbable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  ipc_entry_gen_rolled (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipc_entry_new_gen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipc_entry_new_rollpoint (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipc_space_get_rollpoint (TYPE_1__*) ; 

kern_return_t
ipc_entry_claim(
	ipc_space_t		space,
	mach_port_name_t	*namep,
	ipc_entry_t		*entryp)
{
	ipc_entry_t entry;
	ipc_entry_t table;
	mach_port_index_t first_free;
	mach_port_gen_t gen;
	mach_port_name_t new_name;

	table = &space->is_table[0];

	first_free = table->ie_next;
	assert(first_free != 0);

	entry = &table[first_free];
	table->ie_next = entry->ie_next;
	space->is_table_free--;

	assert(table->ie_next < space->is_table_size);

	/*
	 *	Initialize the new entry: increment gencount and reset
	 *	rollover point if it rolled over, and clear ie_request.
	 */
	gen = ipc_entry_new_gen(entry->ie_bits);
	if (__improbable(ipc_entry_gen_rolled(entry->ie_bits, gen))) {
		ipc_entry_bits_t roll = ipc_space_get_rollpoint(space);
		gen = ipc_entry_new_rollpoint(roll);
	}
	entry->ie_bits = gen;
	entry->ie_request = IE_REQ_NONE;

	/*
	 *	The new name can't be MACH_PORT_NULL because index
	 *	is non-zero.  It can't be MACH_PORT_DEAD because
	 *	the table isn't allowed to grow big enough.
	 *	(See comment in ipc/ipc_table.h.)
	 */
	new_name = MACH_PORT_MAKE(first_free, gen);
	assert(MACH_PORT_VALID(new_name));
	*namep = new_name;
	*entryp = entry;

	return KERN_SUCCESS;
}