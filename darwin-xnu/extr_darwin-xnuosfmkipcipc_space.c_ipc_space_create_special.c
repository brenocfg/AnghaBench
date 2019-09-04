#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  TYPE_1__* ipc_space_t ;
struct TYPE_6__ {int is_bits; int /*<<< orphan*/  is_node_id; scalar_t__ is_high_mod; scalar_t__ is_low_mod; scalar_t__ is_table_next; int /*<<< orphan*/  is_task; int /*<<< orphan*/  is_table; } ;

/* Variables and functions */
 int /*<<< orphan*/  HOST_LOCAL_NODE ; 
 int /*<<< orphan*/  IE_NULL ; 
 int IS_INACTIVE ; 
 TYPE_1__* IS_NULL ; 
 int /*<<< orphan*/  KERN_RESOURCE_SHORTAGE ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int /*<<< orphan*/  TASK_NULL ; 
 TYPE_1__* is_alloc () ; 
 int /*<<< orphan*/  is_lock_init (TYPE_1__*) ; 

kern_return_t
ipc_space_create_special(
	ipc_space_t	*spacep)
{
	ipc_space_t space;

	space = is_alloc();
	if (space == IS_NULL)
		return KERN_RESOURCE_SHORTAGE;

	is_lock_init(space);

	space->is_bits       = IS_INACTIVE | 1; /* 1 ref, not active, not growing */
	space->is_table      = IE_NULL;
	space->is_task       = TASK_NULL;
	space->is_table_next = 0;
	space->is_low_mod    = 0;
	space->is_high_mod   = 0;
	space->is_node_id = HOST_LOCAL_NODE; /* HOST_LOCAL_NODE, except proxy spaces */

	*spacep = space;
	return KERN_SUCCESS;
}