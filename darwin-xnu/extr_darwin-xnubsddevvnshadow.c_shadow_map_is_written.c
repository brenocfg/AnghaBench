#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_5__ {int* block_bitmap; } ;
typedef  TYPE_1__ shadow_map_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_6__ {size_t byte; int /*<<< orphan*/  bit; } ;
typedef  TYPE_2__ bitmap_offset_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int bit (int /*<<< orphan*/ ) ; 
 TYPE_2__ bitmap_offset (int /*<<< orphan*/ ) ; 

boolean_t
shadow_map_is_written(shadow_map_t * map, uint32_t block_offset)
{
    bitmap_offset_t 	b;

    b = bitmap_offset(block_offset);
    return ((map->block_bitmap[b.byte] & bit(b.bit)) ? TRUE : FALSE);
}