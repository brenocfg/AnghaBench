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
typedef  int /*<<< orphan*/  u32 ;
struct efx_nic {struct efx_filter_state* filter_state; } ;
struct efx_filter_table {unsigned int size; TYPE_1__* spec; int /*<<< orphan*/  used_bitmap; } ;
struct efx_filter_state {int /*<<< orphan*/  lock; struct efx_filter_table* table; } ;
typedef  int /*<<< orphan*/  s32 ;
typedef  enum efx_filter_table_id { ____Placeholder_efx_filter_table_id } efx_filter_table_id ;
typedef  enum efx_filter_priority { ____Placeholder_efx_filter_priority } efx_filter_priority ;
struct TYPE_2__ {int priority; } ;

/* Variables and functions */
 int EFX_FILTER_TABLE_RX_DEF ; 
 int EFX_FILTER_TABLE_RX_IP ; 
 int /*<<< orphan*/  EMSGSIZE ; 
 int /*<<< orphan*/  efx_filter_make_id (TYPE_1__*,unsigned int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (unsigned int,int /*<<< orphan*/ ) ; 

s32 efx_filter_get_rx_ids(struct efx_nic *efx,
			  enum efx_filter_priority priority,
			  u32 *buf, u32 size)
{
	struct efx_filter_state *state = efx->filter_state;
	enum efx_filter_table_id table_id;
	struct efx_filter_table *table;
	unsigned int filter_idx;
	s32 count = 0;

	spin_lock_bh(&state->lock);

	for (table_id = EFX_FILTER_TABLE_RX_IP;
	     table_id <= EFX_FILTER_TABLE_RX_DEF;
	     table_id++) {
		table = &state->table[table_id];
		for (filter_idx = 0; filter_idx < table->size; filter_idx++) {
			if (test_bit(filter_idx, table->used_bitmap) &&
			    table->spec[filter_idx].priority == priority) {
				if (count == size) {
					count = -EMSGSIZE;
					goto out;
				}
				buf[count++] = efx_filter_make_id(
					&table->spec[filter_idx], filter_idx);
			}
		}
	}
out:
	spin_unlock_bh(&state->lock);

	return count;
}