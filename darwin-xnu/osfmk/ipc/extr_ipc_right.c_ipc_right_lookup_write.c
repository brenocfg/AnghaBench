#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  mach_port_name_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  scalar_t__ ipc_space_t ;
typedef  int /*<<< orphan*/  ipc_entry_t ;

/* Variables and functions */
 int /*<<< orphan*/  IE_NULL ; 
 scalar_t__ IS_NULL ; 
 int /*<<< orphan*/  KERN_INVALID_NAME ; 
 int /*<<< orphan*/  KERN_INVALID_TASK ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  ipc_entry_lookup (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_active (scalar_t__) ; 
 int /*<<< orphan*/  is_write_lock (scalar_t__) ; 
 int /*<<< orphan*/  is_write_unlock (scalar_t__) ; 

kern_return_t
ipc_right_lookup_write(
	ipc_space_t		space,
	mach_port_name_t	name,
	ipc_entry_t		*entryp)
{
	ipc_entry_t entry;

	assert(space != IS_NULL);

	is_write_lock(space);

	if (!is_active(space)) {
		is_write_unlock(space);
		return KERN_INVALID_TASK;
	}

	if ((entry = ipc_entry_lookup(space, name)) == IE_NULL) {
		is_write_unlock(space);
		return KERN_INVALID_NAME;
	}

	*entryp = entry;
	return KERN_SUCCESS;
}