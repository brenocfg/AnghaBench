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
typedef  scalar_t__ sector_t ;

/* Variables and functions */
 int /*<<< orphan*/  clear_bit (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ do_div (scalar_t__,unsigned int) ; 
 scalar_t__ map_size ; 
 int /*<<< orphan*/  map_storep ; 
 unsigned int scsi_debug_unmap_alignment ; 
 unsigned int scsi_debug_unmap_granularity ; 

__attribute__((used)) static void unmap_region(sector_t lba, unsigned int len)
{
	unsigned int granularity, alignment;
	sector_t end = lba + len;

	granularity = scsi_debug_unmap_granularity;
	alignment = granularity - scsi_debug_unmap_alignment;

	while (lba < end) {
		sector_t block, rem;

		block = lba + alignment;
		rem = do_div(block, granularity);

		if (rem == 0 && lba + granularity < end && block < map_size)
			clear_bit(block, map_storep);

		lba += granularity - rem;
	}
}