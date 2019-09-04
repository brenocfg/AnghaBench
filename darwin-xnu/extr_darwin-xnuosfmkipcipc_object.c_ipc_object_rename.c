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
typedef  scalar_t__ kern_return_t ;
typedef  int /*<<< orphan*/  ipc_space_t ;
typedef  int /*<<< orphan*/  ipc_entry_t ;

/* Variables and functions */
 int /*<<< orphan*/  IE_NULL ; 
 scalar_t__ KERN_INVALID_NAME ; 
 scalar_t__ KERN_NAME_EXISTS ; 
 scalar_t__ KERN_SUCCESS ; 
 scalar_t__ ipc_entry_alloc_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipc_entry_dealloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipc_entry_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ipc_right_inuse (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ipc_right_rename (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_write_unlock (int /*<<< orphan*/ ) ; 

kern_return_t
ipc_object_rename(
	ipc_space_t		space,
	mach_port_name_t	oname,
	mach_port_name_t	nname)
{
	ipc_entry_t oentry, nentry;
	kern_return_t kr;
	
	kr = ipc_entry_alloc_name(space, nname, &nentry);
	if (kr != KERN_SUCCESS)
		return kr;

	/* space is write-locked and active */

	if (ipc_right_inuse(space, nname, nentry)) {
		/* space is unlocked */
		return KERN_NAME_EXISTS;
	}

	/* don't let ipc_entry_lookup see the uninitialized new entry */

	if ((oname == nname) ||
	    ((oentry = ipc_entry_lookup(space, oname)) == IE_NULL)) {
		ipc_entry_dealloc(space, nname, nentry);
		is_write_unlock(space);
		return KERN_INVALID_NAME;
	}

	kr = ipc_right_rename(space, oname, oentry, nname, nentry);
	/* space is unlocked */
	return kr;
}