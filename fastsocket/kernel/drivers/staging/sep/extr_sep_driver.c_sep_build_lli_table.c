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
struct sep_lli_entry_t {unsigned long physical_address; unsigned long block_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  dbg (char*) ; 
 int /*<<< orphan*/  edbg (char*,...) ; 

__attribute__((used)) static void sep_build_lli_table(struct sep_lli_entry_t *lli_array_ptr, struct sep_lli_entry_t *lli_table_ptr, unsigned long *num_processed_entries_ptr, unsigned long *num_table_entries_ptr, unsigned long table_data_size)
{
	unsigned long curr_table_data_size;
	/* counter of lli array entry */
	unsigned long array_counter;

	dbg("SEP Driver:--------> sep_build_lli_table start\n");

	/* init currrent table data size and lli array entry counter */
	curr_table_data_size = 0;
	array_counter = 0;
	*num_table_entries_ptr = 1;

	edbg("SEP Driver:table_data_size is %lu\n", table_data_size);

	/* fill the table till table size reaches the needed amount */
	while (curr_table_data_size < table_data_size) {
		/* update the number of entries in table */
		(*num_table_entries_ptr)++;

		lli_table_ptr->physical_address = lli_array_ptr[array_counter].physical_address;
		lli_table_ptr->block_size = lli_array_ptr[array_counter].block_size;
		curr_table_data_size += lli_table_ptr->block_size;

		edbg("SEP Driver:lli_table_ptr is %08lx\n", (unsigned long) lli_table_ptr);
		edbg("SEP Driver:lli_table_ptr->physical_address is %08lx\n", lli_table_ptr->physical_address);
		edbg("SEP Driver:lli_table_ptr->block_size is %lu\n", lli_table_ptr->block_size);

		/* check for overflow of the table data */
		if (curr_table_data_size > table_data_size) {
			edbg("SEP Driver:curr_table_data_size > table_data_size\n");

			/* update the size of block in the table */
			lli_table_ptr->block_size -= (curr_table_data_size - table_data_size);

			/* update the physical address in the lli array */
			lli_array_ptr[array_counter].physical_address += lli_table_ptr->block_size;

			/* update the block size left in the lli array */
			lli_array_ptr[array_counter].block_size = (curr_table_data_size - table_data_size);
		} else
			/* advance to the next entry in the lli_array */
			array_counter++;

		edbg("SEP Driver:lli_table_ptr->physical_address is %08lx\n", lli_table_ptr->physical_address);
		edbg("SEP Driver:lli_table_ptr->block_size is %lu\n", lli_table_ptr->block_size);

		/* move to the next entry in table */
		lli_table_ptr++;
	}

	/* set the info entry to default */
	lli_table_ptr->physical_address = 0xffffffff;
	lli_table_ptr->block_size = 0;

	edbg("SEP Driver:lli_table_ptr is %08lx\n", (unsigned long) lli_table_ptr);
	edbg("SEP Driver:lli_table_ptr->physical_address is %08lx\n", lli_table_ptr->physical_address);
	edbg("SEP Driver:lli_table_ptr->block_size is %lu\n", lli_table_ptr->block_size);

	/* set the output parameter */
	*num_processed_entries_ptr += array_counter;

	edbg("SEP Driver:*num_processed_entries_ptr is %lu\n", *num_processed_entries_ptr);
	dbg("SEP Driver:<-------- sep_build_lli_table end\n");
	return;
}