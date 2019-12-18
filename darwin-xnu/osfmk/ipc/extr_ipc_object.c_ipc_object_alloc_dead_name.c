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
typedef  int /*<<< orphan*/  mach_port_name_t ;
typedef  scalar_t__ kern_return_t ;
typedef  int /*<<< orphan*/  ipc_space_t ;
typedef  TYPE_1__* ipc_entry_t ;
struct TYPE_5__ {scalar_t__ ie_object; int ie_bits; } ;

/* Variables and functions */
 scalar_t__ IO_NULL ; 
 scalar_t__ KERN_NAME_EXISTS ; 
 scalar_t__ KERN_SUCCESS ; 
 int MACH_PORT_TYPE_DEAD_NAME ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ ipc_entry_alloc_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__**) ; 
 int /*<<< orphan*/  ipc_entry_modified (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ ipc_right_inuse (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  is_write_unlock (int /*<<< orphan*/ ) ; 

kern_return_t
ipc_object_alloc_dead_name(
	ipc_space_t		space,
	mach_port_name_t	name)
{
	ipc_entry_t entry;
	kern_return_t kr;

	kr = ipc_entry_alloc_name(space, name, &entry);
	if (kr != KERN_SUCCESS)
		return kr;
	/* space is write-locked */

	if (ipc_right_inuse(space, name, entry))
		return KERN_NAME_EXISTS;

	/* null object, MACH_PORT_TYPE_DEAD_NAME, 1 uref */

	assert(entry->ie_object == IO_NULL);
	entry->ie_bits |= MACH_PORT_TYPE_DEAD_NAME | 1;
	ipc_entry_modified(space, name, entry);
	is_write_unlock(space);
	return KERN_SUCCESS;
}