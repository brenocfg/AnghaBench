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
struct TYPE_3__ {int shadow_size_bands; int blocks_per_band; } ;
typedef  TYPE_1__ shadow_map_t ;

/* Variables and functions */

uint32_t
shadow_map_shadow_size(shadow_map_t * map)
{
    return (map->shadow_size_bands * map->blocks_per_band);
}