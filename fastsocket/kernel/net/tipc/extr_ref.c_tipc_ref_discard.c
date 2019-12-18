#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct reference {size_t ref; int /*<<< orphan*/ * object; } ;
struct TYPE_2__ {size_t index_mask; size_t first_free; size_t last_free; struct reference* entries; } ;

/* Variables and functions */
 int /*<<< orphan*/  err (char*) ; 
 int /*<<< orphan*/  ref_table_lock ; 
 TYPE_1__ tipc_ref_table ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

void tipc_ref_discard(u32 ref)
{
	struct reference *entry;
	u32 index;
	u32 index_mask;

	if (!tipc_ref_table.entries) {
		err("Reference table not found during discard attempt\n");
		return;
	}

	index_mask = tipc_ref_table.index_mask;
	index = ref & index_mask;
	entry = &(tipc_ref_table.entries[index]);

	write_lock_bh(&ref_table_lock);

	if (!entry->object) {
		err("Attempt to discard reference to non-existent object\n");
		goto exit;
	}
	if (entry->ref != ref) {
		err("Attempt to discard non-existent reference\n");
		goto exit;
	}

	/*
	 * mark entry as unused; increment instance part of entry's reference
	 * to invalidate any subsequent references
	 */

	entry->object = NULL;
	entry->ref = (ref & ~index_mask) + (index_mask + 1);

	/* append entry to free entry list */

	if (tipc_ref_table.first_free == 0)
		tipc_ref_table.first_free = index;
	else
		tipc_ref_table.entries[tipc_ref_table.last_free].ref |= index;
	tipc_ref_table.last_free = index;

exit:
	write_unlock_bh(&ref_table_lock);
}