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
struct TYPE_5__ {scalar_t__ blocks_per_band; } ;
typedef  TYPE_1__ shadow_map_t ;
typedef  scalar_t__ boolean_t ;
typedef  scalar_t__ band_number_t ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ my_trunc (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  printf (char*) ; 
 scalar_t__ shadow_map_block_to_band (TYPE_1__*,scalar_t__) ; 
 scalar_t__ shadow_map_mapped_band (TYPE_1__*,scalar_t__,scalar_t__,scalar_t__*) ; 

__attribute__((used)) static uint32_t
shadow_map_contiguous(shadow_map_t * map, uint32_t start_block,
		      uint32_t num_blocks, boolean_t is_write)
{
    band_number_t	band = shadow_map_block_to_band(map, start_block);
    uint32_t		end_block = start_block + num_blocks;
    boolean_t		is_mapped;
    band_number_t	mapped_band;
    uint32_t		ret_end_block = end_block;
    uint32_t		p;

    is_mapped = shadow_map_mapped_band(map, band, is_write, &mapped_band);
    if (is_write == FALSE && is_mapped == FALSE) {
	static int happened = 0;
	/* this can't happen */
	if (happened == 0) {
	    printf("shadow_map_contiguous: this can't happen!\n");
	    happened = 1;
	}
	return (start_block);
    }
    for (p = my_trunc(start_block + map->blocks_per_band, 
		      map->blocks_per_band);
	 p < end_block; p += map->blocks_per_band) {
	band_number_t 	next_mapped_band;
		
	band++;
	is_mapped = shadow_map_mapped_band(map, band, is_write,
					   &next_mapped_band);
	if (is_write == FALSE && is_mapped == FALSE) {
	    return (p);
	}
	if ((mapped_band + 1) != next_mapped_band) {
	    /* not contiguous */
	    ret_end_block = p;
	    break;
	}
	mapped_band = next_mapped_band;
    }
    return (ret_end_block);
}