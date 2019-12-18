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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct efx_nic {struct efx_filter_state* filter_state; } ;
struct efx_filter_table {unsigned int size; scalar_t__ used; int /*<<< orphan*/  used_bitmap; struct efx_filter_spec* spec; } ;
struct efx_filter_state {int /*<<< orphan*/  lock; struct efx_filter_table* table; } ;
struct efx_filter_spec {int priority; } ;
typedef  enum efx_filter_table_id { ____Placeholder_efx_filter_table_id } efx_filter_table_id ;
typedef  enum efx_filter_priority { ____Placeholder_efx_filter_priority } efx_filter_priority ;

/* Variables and functions */
 unsigned int EFX_FILTER_TABLE_COUNT ; 
 int ENOENT ; 
 int /*<<< orphan*/  efx_filter_id_flags (int /*<<< orphan*/ ) ; 
 unsigned int efx_filter_id_index (int /*<<< orphan*/ ) ; 
 int efx_filter_id_table_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  efx_filter_table_clear_entry (struct efx_nic*,struct efx_filter_table*,unsigned int) ; 
 int /*<<< orphan*/  efx_filter_table_reset_search_depth (struct efx_filter_table*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (unsigned int,int /*<<< orphan*/ ) ; 

int efx_filter_remove_id_safe(struct efx_nic *efx,
			      enum efx_filter_priority priority,
			      u32 filter_id)
{
	struct efx_filter_state *state = efx->filter_state;
	enum efx_filter_table_id table_id;
	struct efx_filter_table *table;
	unsigned int filter_idx;
	struct efx_filter_spec *spec;
	u8 filter_flags;
	int rc;

	table_id = efx_filter_id_table_id(filter_id);
	if ((unsigned int)table_id >= EFX_FILTER_TABLE_COUNT)
		return -ENOENT;
	table = &state->table[table_id];

	filter_idx = efx_filter_id_index(filter_id);
	if (filter_idx >= table->size)
		return -ENOENT;
	spec = &table->spec[filter_idx];

	filter_flags = efx_filter_id_flags(filter_id);

	spin_lock_bh(&state->lock);

	if (test_bit(filter_idx, table->used_bitmap) &&
	    spec->priority == priority) {
		efx_filter_table_clear_entry(efx, table, filter_idx);
		if (table->used == 0)
			efx_filter_table_reset_search_depth(table);
		rc = 0;
	} else {
		rc = -ENOENT;
	}

	spin_unlock_bh(&state->lock);

	return rc;
}