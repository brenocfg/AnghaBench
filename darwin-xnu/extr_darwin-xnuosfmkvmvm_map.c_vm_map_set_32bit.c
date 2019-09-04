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
typedef  TYPE_1__* vm_map_t ;
typedef  scalar_t__ vm_map_offset_t ;
struct TYPE_3__ {scalar_t__ max_offset; } ;

/* Variables and functions */
 scalar_t__ VM_MAX_ADDRESS ; 

void
vm_map_set_32bit(vm_map_t map)
{
#if defined(__arm__) || defined(__arm64__)
	map->max_offset = pmap_max_offset(FALSE, ARM_PMAP_MAX_OFFSET_DEVICE);
#else
	map->max_offset = (vm_map_offset_t)VM_MAX_ADDRESS;
#endif
}