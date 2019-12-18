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
 size_t s_get_num_reserved_regions () ; 
 size_t soc_memory_region_count ; 

size_t soc_get_available_memory_region_max_count(void)
{
    /* Worst-case: each reserved memory region splits an available
       region in two, so the maximum possible number of regions
       is the number of regions of memory plus the number of reservations */
    return soc_memory_region_count + s_get_num_reserved_regions();
}