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
struct partition {int data_sectors_per_block; int /*<<< orphan*/ * header_cache; } ;
struct block {int free_sectors; } ;

/* Variables and functions */
 int HEADER_MAP_OFFSET ; 
 scalar_t__ SECTOR_FREE ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int find_free_sector(const struct partition *part, const struct block *block)
{
	int i, stop;

	i = stop = part->data_sectors_per_block - block->free_sectors;

	do {
		if (le16_to_cpu(part->header_cache[HEADER_MAP_OFFSET + i])
				== SECTOR_FREE)
			return i;

		if (++i == part->data_sectors_per_block)
			i = 0;
	}
	while(i != stop);

	return -1;
}