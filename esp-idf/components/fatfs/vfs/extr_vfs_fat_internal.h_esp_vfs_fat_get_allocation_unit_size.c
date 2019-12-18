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
 size_t MAX (size_t,size_t) ; 
 size_t MIN (size_t,size_t const) ; 

__attribute__((used)) static inline size_t esp_vfs_fat_get_allocation_unit_size(
        size_t sector_size, size_t requested_size)
{
    size_t alloc_unit_size = requested_size;
    const size_t max_sectors_per_cylinder = 128;
    const size_t max_size = sector_size * max_sectors_per_cylinder;
    alloc_unit_size = MAX(alloc_unit_size, sector_size);
    alloc_unit_size = MIN(alloc_unit_size, max_size);
    return alloc_unit_size;
}