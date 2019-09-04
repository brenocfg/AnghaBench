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
typedef  scalar_t__ kern_return_t ;
typedef  scalar_t__ ipc_space_t ;

/* Variables and functions */
 scalar_t__ IS_NULL ; 
 scalar_t__ KERN_INVALID_TASK ; 
 scalar_t__ KERN_SUCCESS ; 
 scalar_t__ ipc_entry_grow_table (scalar_t__,int) ; 
 int /*<<< orphan*/  is_active (scalar_t__) ; 
 int /*<<< orphan*/  is_write_lock (scalar_t__) ; 
 int /*<<< orphan*/  is_write_unlock (scalar_t__) ; 

kern_return_t
task_set_port_space(
 	ipc_space_t	space,
 	int		table_entries)
{
	kern_return_t kr;
	
	if (space == IS_NULL)
		return KERN_INVALID_TASK;

	is_write_lock(space);

	if (!is_active(space)) {
		is_write_unlock(space);
		return KERN_INVALID_TASK;
	}

	kr = ipc_entry_grow_table(space, table_entries);
	if (kr == KERN_SUCCESS)
		is_write_unlock(space);
	return kr;
}