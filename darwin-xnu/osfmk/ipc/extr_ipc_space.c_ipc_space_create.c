#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct ipc_entry {int dummy; } ;
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  TYPE_1__* ipc_table_size_t ;
typedef  TYPE_2__* ipc_space_t ;
typedef  scalar_t__ ipc_entry_t ;
typedef  int ipc_entry_num_t ;
struct TYPE_12__ {int is_bits; int is_table_size; int is_table_free; int is_low_mod; int /*<<< orphan*/  is_node_id; scalar_t__ is_high_mod; int /*<<< orphan*/ * is_task; TYPE_1__* is_table_next; scalar_t__ is_table; int /*<<< orphan*/  bool_gen; scalar_t__ is_entropy; } ;
struct TYPE_11__ {int its_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  HOST_LOCAL_NODE ; 
 scalar_t__ IE_NULL ; 
 TYPE_2__* IS_NULL ; 
 int /*<<< orphan*/  KERN_RESOURCE_SHORTAGE ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int /*<<< orphan*/  ipc_space_rand_freelist (TYPE_2__*,scalar_t__,int /*<<< orphan*/ ,int) ; 
 TYPE_2__* is_alloc () ; 
 int /*<<< orphan*/  is_free (TYPE_2__*) ; 
 int /*<<< orphan*/  is_lock_init (TYPE_2__*) ; 
 scalar_t__ it_entries_alloc (TYPE_1__*) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  random_bool_init (int /*<<< orphan*/ *) ; 

kern_return_t
ipc_space_create(
	ipc_table_size_t	initial,
	ipc_space_t		*spacep)
{
	ipc_space_t space;
	ipc_entry_t table;
	ipc_entry_num_t new_size;

	space = is_alloc();
	if (space == IS_NULL)
		return KERN_RESOURCE_SHORTAGE;

	table = it_entries_alloc(initial);
	if (table == IE_NULL) {
		is_free(space);
		return KERN_RESOURCE_SHORTAGE;
	}

	new_size = initial->its_size;
	memset((void *) table, 0, new_size * sizeof(struct ipc_entry));

	/* Set to 0 so entropy pool refills */
	memset((void *) space->is_entropy, 0, sizeof(space->is_entropy));

	random_bool_init(&space->bool_gen);
	ipc_space_rand_freelist(space, table, 0, new_size);

	is_lock_init(space);
	space->is_bits = 2; /* 2 refs, active, not growing */
	space->is_table_size = new_size;
	space->is_table_free = new_size - 1;
	space->is_table = table;
	space->is_table_next = initial+1;
	space->is_task = NULL;
	space->is_low_mod = new_size;
	space->is_high_mod = 0;
	space->is_node_id = HOST_LOCAL_NODE; /* HOST_LOCAL_NODE, except proxy spaces */

	*spacep = space;
	return KERN_SUCCESS;
}