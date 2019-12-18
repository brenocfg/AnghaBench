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
struct sep_lli_entry_t {int block_size; scalar_t__ physical_address; } ;
struct sep_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dbg (char*) ; 
 int /*<<< orphan*/  edbg (char*,unsigned long,...) ; 
 scalar_t__ sep_shared_bus_to_virt (struct sep_device*,unsigned long) ; 

__attribute__((used)) static void sep_debug_print_lli_tables(struct sep_device *sep, struct sep_lli_entry_t *lli_table_ptr, unsigned long num_table_entries, unsigned long table_data_size)
{
	unsigned long table_count;
	unsigned long entries_count;

	dbg("SEP Driver:--------> sep_debug_print_lli_tables start\n");

	table_count = 1;
	while ((unsigned long) lli_table_ptr != 0xffffffff) {
		edbg("SEP Driver: lli table %08lx, table_data_size is %lu\n", table_count, table_data_size);
		edbg("SEP Driver: num_table_entries is %lu\n", num_table_entries);

		/* print entries of the table (without info entry) */
		for (entries_count = 0; entries_count < num_table_entries; entries_count++, lli_table_ptr++) {
			edbg("SEP Driver:lli_table_ptr address is %08lx\n", (unsigned long) lli_table_ptr);
			edbg("SEP Driver:phys address is %08lx block size is %lu\n", lli_table_ptr->physical_address, lli_table_ptr->block_size);
		}

		/* point to the info entry */
		lli_table_ptr--;

		edbg("SEP Driver:phys lli_table_ptr->block_size is %lu\n", lli_table_ptr->block_size);
		edbg("SEP Driver:phys lli_table_ptr->physical_address is %08lx\n", lli_table_ptr->physical_address);


		table_data_size = lli_table_ptr->block_size & 0xffffff;
		num_table_entries = (lli_table_ptr->block_size >> 24) & 0xff;
		lli_table_ptr = (struct sep_lli_entry_t *)
		    (lli_table_ptr->physical_address);

		edbg("SEP Driver:phys table_data_size is %lu num_table_entries is %lu lli_table_ptr is%lu\n", table_data_size, num_table_entries, (unsigned long) lli_table_ptr);

		if ((unsigned long) lli_table_ptr != 0xffffffff)
			lli_table_ptr = (struct sep_lli_entry_t *) sep_shared_bus_to_virt(sep, (unsigned long) lli_table_ptr);

		table_count++;
	}
	dbg("SEP Driver:<-------- sep_debug_print_lli_tables end\n");
}