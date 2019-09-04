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
 int /*<<< orphan*/  ITS_SIZE_NONE ; 
 scalar_t__ KERN_INVALID_TASK ; 
 scalar_t__ KERN_SUCCESS ; 
 scalar_t__ ipc_entry_get (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ ipc_entry_grow_table (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_active (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_write_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_write_unlock (int /*<<< orphan*/ ) ; 

kern_return_t
ipc_entry_alloc(
	ipc_space_t		space,
	mach_port_name_t	*namep,
	ipc_entry_t		*entryp)
{
	kern_return_t kr;

	is_write_lock(space);

	for (;;) {
		if (!is_active(space)) {
			is_write_unlock(space);
			return KERN_INVALID_TASK;
		}

		kr = ipc_entry_get(space, namep, entryp);
		if (kr == KERN_SUCCESS)
			return kr;

		kr = ipc_entry_grow_table(space, ITS_SIZE_NONE);
		if (kr != KERN_SUCCESS)
			return kr; /* space is unlocked */
	}
}