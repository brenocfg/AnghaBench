#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_3__ {int blocks_per_band; } ;
typedef  TYPE_1__ shadow_map_t ;
typedef  int band_number_t ;

/* Variables and functions */

__attribute__((used)) static __inline__ band_number_t
shadow_map_block_to_band(shadow_map_t * map, uint32_t block)
{
    return (block / map->blocks_per_band);
}