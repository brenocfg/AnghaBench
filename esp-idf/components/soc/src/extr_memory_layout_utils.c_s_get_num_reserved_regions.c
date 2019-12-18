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

/* Variables and functions */
 size_t EXTRA_RESERVED_REGIONS ; 
 int /*<<< orphan*/  soc_reserved_memory_region_end ; 
 int /*<<< orphan*/  soc_reserved_memory_region_start ; 

__attribute__((used)) static size_t s_get_num_reserved_regions(void)
{
    return ( ( &soc_reserved_memory_region_end
               - &soc_reserved_memory_region_start ) +
             EXTRA_RESERVED_REGIONS );
}