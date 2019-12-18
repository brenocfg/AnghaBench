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
struct sep_lli_entry_t {unsigned long block_size; scalar_t__ physical_address; } ;
struct page {int dummy; } ;

/* Variables and functions */
 unsigned long SEP_NUM_ENTRIES_MASK ; 
 unsigned long SEP_NUM_ENTRIES_OFFSET_IN_BITS ; 
 int /*<<< orphan*/  sep_free_dma_pages (struct page**,unsigned long,int) ; 

__attribute__((used)) static void sep_deallocated_flow_tables(struct sep_lli_entry_t *first_table_ptr)
{
	/* id pointer */
	unsigned long *table_ptr;
	/* end address of the flow dma area */
	unsigned long num_entries;
	unsigned long num_pages;
	struct page **pages_ptr;
	/* maximum table size in words */
	struct sep_lli_entry_t *info_entry_ptr;

	/* set the pointer to the first table */
	table_ptr = (unsigned long *) first_table_ptr->physical_address;

	/* set the num of entries */
	num_entries = (first_table_ptr->block_size >> SEP_NUM_ENTRIES_OFFSET_IN_BITS)
	    & SEP_NUM_ENTRIES_MASK;

	/* go over all the connected tables */
	while (*table_ptr != 0xffffffff) {
		/* get number of pages */
		num_pages = *(table_ptr - 2);

		/* get the pointer to the pages */
		pages_ptr = (struct page **) (*(table_ptr - 1));

		/* free the pages */
		sep_free_dma_pages(pages_ptr, num_pages, 1);

		/* goto to the info entry */
		info_entry_ptr = ((struct sep_lli_entry_t *) table_ptr) + (num_entries - 1);

		table_ptr = (unsigned long *) info_entry_ptr->physical_address;
		num_entries = (info_entry_ptr->block_size >> SEP_NUM_ENTRIES_OFFSET_IN_BITS) & SEP_NUM_ENTRIES_MASK;
	}

	return;
}