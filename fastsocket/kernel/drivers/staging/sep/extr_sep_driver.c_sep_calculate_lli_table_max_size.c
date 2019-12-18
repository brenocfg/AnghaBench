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
struct sep_lli_entry_t {scalar_t__ block_size; } ;

/* Variables and functions */
 int SEP_DRIVER_ENTRIES_PER_TABLE_IN_SEP ; 

__attribute__((used)) static unsigned long sep_calculate_lli_table_max_size(struct sep_lli_entry_t *lli_in_array_ptr, unsigned long num_array_entries)
{
	unsigned long table_data_size = 0;
	unsigned long counter;

	/* calculate the data in the out lli table if till we fill the whole
	   table or till the data has ended */
	for (counter = 0; (counter < (SEP_DRIVER_ENTRIES_PER_TABLE_IN_SEP - 1)) && (counter < num_array_entries); counter++)
		table_data_size += lli_in_array_ptr[counter].block_size;
	return table_data_size;
}