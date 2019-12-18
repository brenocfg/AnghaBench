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
struct sep_lli_entry_t {int physical_address; unsigned long block_size; } ;
struct sep_flow_context_t {int dummy; } ;
struct sep_device {int dummy; } ;
struct page {int dummy; } ;

/* Variables and functions */
 unsigned long SEP_NUM_ENTRIES_OFFSET_IN_BITS ; 
 int /*<<< orphan*/  kfree (struct sep_lli_entry_t*) ; 
 int sep_find_free_flow_dma_table_space (struct sep_device*,unsigned long**) ; 
 int sep_lock_kernel_pages (struct sep_device*,unsigned long,unsigned long,unsigned long*,struct sep_lli_entry_t**,struct page***) ; 
 int sep_lock_user_pages (struct sep_device*,unsigned long,unsigned long,unsigned long*,struct sep_lli_entry_t**,struct page***) ; 
 int virt_to_phys (unsigned long*) ; 

__attribute__((used)) static int sep_prepare_one_flow_dma_table(struct sep_device *sep,
					unsigned long virt_buff_addr,
					unsigned long virt_buff_size,
					struct sep_lli_entry_t *table_data,
					struct sep_lli_entry_t **info_entry_ptr,
					struct sep_flow_context_t *flow_data_ptr,
					bool isKernelVirtualAddress)
{
	int error;
	/* the range in pages */
	unsigned long lli_array_size;
	struct sep_lli_entry_t *lli_array;
	struct sep_lli_entry_t *flow_dma_table_entry_ptr;
	unsigned long *start_dma_table_ptr;
	/* total table data counter */
	unsigned long dma_table_data_count;
	/* pointer that will keep the pointer to the pages of the virtual buffer */
	struct page **page_array_ptr;
	unsigned long entry_count;

	/* find the space for the new table */
	error = sep_find_free_flow_dma_table_space(sep, &start_dma_table_ptr);
	if (error)
		goto end_function;

	/* check if the pages are in Kernel Virtual Address layout */
	if (isKernelVirtualAddress == true)
		/* lock kernel buffer in the memory */
		error = sep_lock_kernel_pages(sep, virt_buff_addr, virt_buff_size, &lli_array_size, &lli_array, &page_array_ptr);
	else
		/* lock user buffer in the memory */
		error = sep_lock_user_pages(sep, virt_buff_addr, virt_buff_size, &lli_array_size, &lli_array, &page_array_ptr);

	if (error)
		goto end_function;

	/* set the pointer to page array at the beginning of table - this table is
	   now considered taken */
	*start_dma_table_ptr = lli_array_size;

	/* point to the place of the pages pointers of the table */
	start_dma_table_ptr++;

	/* set the pages pointer */
	*start_dma_table_ptr = (unsigned long) page_array_ptr;

	/* set the pointer to the first entry */
	flow_dma_table_entry_ptr = (struct sep_lli_entry_t *) (++start_dma_table_ptr);

	/* now create the entries for table */
	for (dma_table_data_count = entry_count = 0; entry_count < lli_array_size; entry_count++) {
		flow_dma_table_entry_ptr->physical_address = lli_array[entry_count].physical_address;

		flow_dma_table_entry_ptr->block_size = lli_array[entry_count].block_size;

		/* set the total data of a table */
		dma_table_data_count += lli_array[entry_count].block_size;

		flow_dma_table_entry_ptr++;
	}

	/* set the physical address */
	table_data->physical_address = virt_to_phys(start_dma_table_ptr);

	/* set the num_entries and total data size */
	table_data->block_size = ((lli_array_size + 1) << SEP_NUM_ENTRIES_OFFSET_IN_BITS) | (dma_table_data_count);

	/* set the info entry */
	flow_dma_table_entry_ptr->physical_address = 0xffffffff;
	flow_dma_table_entry_ptr->block_size = 0;

	/* set the pointer to info entry */
	*info_entry_ptr = flow_dma_table_entry_ptr;

	/* the array of the lli entries */
	kfree(lli_array);
end_function:
	return error;
}