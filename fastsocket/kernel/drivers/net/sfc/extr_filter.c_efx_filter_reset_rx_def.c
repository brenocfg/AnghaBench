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
struct efx_nic {int n_rx_channels; scalar_t__ rx_scatter; struct efx_filter_state* filter_state; } ;
struct efx_filter_table {int* used_bitmap; struct efx_filter_spec* spec; } ;
struct efx_filter_state {struct efx_filter_table* table; } ;
struct efx_filter_spec {scalar_t__ type; } ;
typedef  enum efx_filter_flags { ____Placeholder_efx_filter_flags } efx_filter_flags ;

/* Variables and functions */
 int EFX_FILTER_FLAG_RX_RSS ; 
 int EFX_FILTER_FLAG_RX_SCATTER ; 
 int /*<<< orphan*/  EFX_FILTER_PRI_MANUAL ; 
 size_t EFX_FILTER_TABLE_RX_DEF ; 
 scalar_t__ EFX_FILTER_UC_DEF ; 
 int /*<<< orphan*/  efx_filter_init_rx (struct efx_filter_spec*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void efx_filter_reset_rx_def(struct efx_nic *efx, unsigned filter_idx)
{
	struct efx_filter_state *state = efx->filter_state;
	struct efx_filter_table *table = &state->table[EFX_FILTER_TABLE_RX_DEF];
	struct efx_filter_spec *spec = &table->spec[filter_idx];
	enum efx_filter_flags flags = 0;

	/* If there's only one channel then disable RSS for non VF
	 * traffic, thereby allowing VFs to use RSS when the PF can't.
	 */
	if (efx->n_rx_channels > 1)
		flags |= EFX_FILTER_FLAG_RX_RSS;

	if (efx->rx_scatter)
		flags |= EFX_FILTER_FLAG_RX_SCATTER;

	efx_filter_init_rx(spec, EFX_FILTER_PRI_MANUAL, flags, 0);
	spec->type = EFX_FILTER_UC_DEF + filter_idx;
	table->used_bitmap[0] |= 1 << filter_idx;
}