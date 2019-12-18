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
struct sep_lli_entry_t {int dummy; } ;
struct sep_device {void* shared_addr; } ;

/* Variables and functions */
 int SEP_DRIVER_FLOW_DMA_TABLES_AREA_OFFSET_IN_BYTES ; 
 int SEP_DRIVER_FLOW_DMA_TABLES_AREA_SIZE_IN_BYTES ; 
 int SEP_DRIVER_MAX_FLOW_NUM_ENTRIES_IN_TABLE ; 

__attribute__((used)) static int sep_find_free_flow_dma_table_space(struct sep_device *sep,
					unsigned long **table_address_ptr)
{
	int error = 0;
	/* pointer to the id field of the flow dma table */
	unsigned long *start_table_ptr;
	/* Do not make start_addr unsigned long * unless fixing the offset
	   computations ! */
	void *flow_dma_area_start_addr;
	unsigned long *flow_dma_area_end_addr;
	/* maximum table size in words */
	unsigned long table_size_in_words;

	/* find the start address of the flow DMA table area */
	flow_dma_area_start_addr = sep->shared_addr + SEP_DRIVER_FLOW_DMA_TABLES_AREA_OFFSET_IN_BYTES;

	/* set end address of the flow table area */
	flow_dma_area_end_addr = flow_dma_area_start_addr + SEP_DRIVER_FLOW_DMA_TABLES_AREA_SIZE_IN_BYTES;

	/* set table size in words */
	table_size_in_words = SEP_DRIVER_MAX_FLOW_NUM_ENTRIES_IN_TABLE * (sizeof(struct sep_lli_entry_t) / sizeof(long)) + 2;

	/* set the pointer to the start address of DMA area */
	start_table_ptr = flow_dma_area_start_addr;

	/* find the space for the next table */
	while (((*start_table_ptr & 0x7FFFFFFF) != 0) && start_table_ptr < flow_dma_area_end_addr)
		start_table_ptr += table_size_in_words;

	/* check if we reached the end of floa tables area */
	if (start_table_ptr >= flow_dma_area_end_addr)
		error = -1;
	else
		*table_address_ptr = start_table_ptr;

	return error;
}