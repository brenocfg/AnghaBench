#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_5__ {scalar_t__ file_size_blocks; scalar_t__* bands; scalar_t__ blocks_per_band; int /*<<< orphan*/  block_bitmap; } ;
typedef  TYPE_1__ shadow_map_t ;
typedef  scalar_t__ boolean_t ;
typedef  scalar_t__ band_number_t ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ bitmap_get (int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  printf (char*,scalar_t__,scalar_t__,scalar_t__) ; 
 size_t shadow_map_block_to_band (TYPE_1__*,scalar_t__) ; 
 scalar_t__ shadow_map_contiguous (TYPE_1__*,scalar_t__,scalar_t__,scalar_t__) ; 

boolean_t
shadow_map_read(shadow_map_t * map, uint32_t block_offset, uint32_t block_count,
		uint32_t * incr_block_offset, uint32_t * incr_block_count)
{
    boolean_t		written = FALSE;
    uint32_t		n_blocks;

    if (block_offset >= map->file_size_blocks
	|| (block_offset + block_count) > map->file_size_blocks) {
	printf("shadow_map_read: request (%d, %d) exceeds file size %d\n",
	       block_offset, block_count, map->file_size_blocks);
	*incr_block_count = 0;
    }
    n_blocks = bitmap_get(map->block_bitmap, block_offset, block_count,
			  &written);
    if (written == FALSE) {
	*incr_block_count = n_blocks;
	*incr_block_offset = block_offset;
    }
    else { /* start has been written, and therefore mapped */
	band_number_t	mapped_band;
	uint32_t		band_limit;
	
	mapped_band = map->bands[shadow_map_block_to_band(map, block_offset)];
	*incr_block_offset = mapped_band * map->blocks_per_band
	    + (block_offset % map->blocks_per_band);
	band_limit 
	    = shadow_map_contiguous(map, block_offset, block_count, FALSE);
	*incr_block_count = band_limit - block_offset;
	if (*incr_block_count > n_blocks) {
	    *incr_block_count = n_blocks;
	}
    }
    return (written);
}