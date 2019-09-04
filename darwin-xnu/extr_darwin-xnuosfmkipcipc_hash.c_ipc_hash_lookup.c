#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mach_port_name_t ;
typedef  TYPE_1__* ipc_space_t ;
typedef  int /*<<< orphan*/  ipc_object_t ;
typedef  int /*<<< orphan*/  ipc_entry_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_3__ {int /*<<< orphan*/  is_table_size; int /*<<< orphan*/  is_table; } ;

/* Variables and functions */
 int /*<<< orphan*/  ipc_hash_table_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

boolean_t
ipc_hash_lookup(
	ipc_space_t		space,
	ipc_object_t		obj,
	mach_port_name_t	*namep,
	ipc_entry_t		*entryp)
{
	return ipc_hash_table_lookup(space->is_table, space->is_table_size, obj, namep, entryp);
}