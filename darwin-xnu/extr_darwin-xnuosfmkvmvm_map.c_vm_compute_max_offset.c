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
typedef  int /*<<< orphan*/  vm_map_offset_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 scalar_t__ MACH_VM_MAX_ADDRESS ; 
 scalar_t__ VM_MAX_ADDRESS ; 

vm_map_offset_t
vm_compute_max_offset(boolean_t is64)
{
#if defined(__arm__) || defined(__arm64__)
	return (pmap_max_offset(is64, ARM_PMAP_MAX_OFFSET_DEVICE));
#else
	return (is64 ? (vm_map_offset_t)MACH_VM_MAX_ADDRESS : (vm_map_offset_t)VM_MAX_ADDRESS);
#endif
}