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
struct efx_nic {int dummy; } ;
struct efx_filter_table {scalar_t__ id; unsigned int step; scalar_t__ offset; int /*<<< orphan*/ * spec; int /*<<< orphan*/  used; int /*<<< orphan*/  used_bitmap; } ;
typedef  int /*<<< orphan*/  efx_oword_t ;

/* Variables and functions */
 scalar_t__ EFX_FILTER_TABLE_RX_DEF ; 
 int /*<<< orphan*/  __clear_bit (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  efx_filter_push_rx_config (struct efx_nic*) ; 
 int /*<<< orphan*/  efx_filter_reset_rx_def (struct efx_nic*,unsigned int) ; 
 int /*<<< orphan*/  efx_writeo (struct efx_nic*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ test_bit (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void efx_filter_table_clear_entry(struct efx_nic *efx,
					 struct efx_filter_table *table,
					 unsigned int filter_idx)
{
	static efx_oword_t filter;

	if (table->id == EFX_FILTER_TABLE_RX_DEF) {
		/* RX default filters must always exist */
		efx_filter_reset_rx_def(efx, filter_idx);
		efx_filter_push_rx_config(efx);
	} else if (test_bit(filter_idx, table->used_bitmap)) {
		__clear_bit(filter_idx, table->used_bitmap);
		--table->used;
		memset(&table->spec[filter_idx], 0, sizeof(table->spec[0]));

		efx_writeo(efx, &filter,
			   table->offset + table->step * filter_idx);
	}
}