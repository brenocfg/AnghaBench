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
typedef  int vm_offset_t ;
typedef  int pmap_paddr_t ;
typedef  int /*<<< orphan*/  addr64_t ;

/* Variables and functions */
 int INTEL_OFFMASK ; 
 int INTEL_PGSHIFT ; 
 int /*<<< orphan*/  kernel_pmap ; 
 scalar_t__ pmap_find_phys (int /*<<< orphan*/ ,int) ; 

addr64_t
kvtophys(
	vm_offset_t addr)
{
	pmap_paddr_t pa;

	pa = ((pmap_paddr_t)pmap_find_phys(kernel_pmap, addr)) << INTEL_PGSHIFT;
	if (pa)
		pa |= (addr & INTEL_OFFMASK);

	return ((addr64_t)pa);
}