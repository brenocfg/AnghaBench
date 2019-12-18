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
typedef  unsigned int sector_t ;

/* Variables and functions */
 int /*<<< orphan*/  do_div (unsigned int,unsigned int) ; 
 unsigned int find_next_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int find_next_zero_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  map_size ; 
 int /*<<< orphan*/  map_storep ; 
 unsigned int scsi_debug_unmap_alignment ; 
 unsigned int scsi_debug_unmap_granularity ; 
 unsigned int test_bit (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int map_state(sector_t lba, unsigned int *num)
{
	unsigned int granularity, alignment, mapped;
	sector_t block, next, end;

	granularity = scsi_debug_unmap_granularity;
	alignment = granularity - scsi_debug_unmap_alignment;
	block = lba + alignment;
	do_div(block, granularity);

	mapped = test_bit(block, map_storep);

	if (mapped)
		next = find_next_zero_bit(map_storep, map_size, block);
	else
		next = find_next_bit(map_storep, map_size, block);

	end = next * granularity - scsi_debug_unmap_alignment;
	*num = end - lba;

	return mapped;
}