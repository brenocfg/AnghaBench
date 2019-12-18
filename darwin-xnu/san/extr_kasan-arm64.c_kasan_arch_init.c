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
 scalar_t__ VM_MAX_KERNEL_ADDRESS ; 
 scalar_t__ VM_MIN_KERNEL_ADDRESS ; 
 int /*<<< orphan*/  kasan_map_shadow (scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  kasan_map_shadow_internal (scalar_t__,scalar_t__,int,int) ; 
 scalar_t__ kernel_vtop ; 
 scalar_t__ physmap_vtop ; 

void
kasan_arch_init(void)
{
	/* Map the physical aperture */
	kasan_map_shadow(kernel_vtop, physmap_vtop - kernel_vtop, true);

#if defined(KERNEL_INTEGRITY_KTRR)
	/* Pre-allocate all the L3 page table pages to avoid triggering KTRR */
	kasan_map_shadow_internal(VM_MIN_KERNEL_ADDRESS, VM_MAX_KERNEL_ADDRESS - VM_MIN_KERNEL_ADDRESS + 1, false, false);
#endif
}