#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vm_offset_t ;
typedef  int /*<<< orphan*/  vm_map_address_t ;
typedef  scalar_t__ pmap_t ;
typedef  scalar_t__ pmap_paddr_t ;
struct TYPE_2__ {int /*<<< orphan*/  map; } ;

/* Variables and functions */
 TYPE_1__* current_thread () ; 
 scalar_t__ kernel_pmap ; 
 scalar_t__ mmu_kvtop (int /*<<< orphan*/ ) ; 
 scalar_t__ mmu_uvtop (int /*<<< orphan*/ ) ; 
 scalar_t__ pmap_extract_internal (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ vm_map_pmap (int /*<<< orphan*/ ) ; 

vm_offset_t
pmap_extract(
	pmap_t pmap,
	vm_map_address_t va)
{
	pmap_paddr_t    pa=0;

	if (pmap == kernel_pmap)
		pa = mmu_kvtop(va);
	else if (pmap == vm_map_pmap(current_thread()->map))
		pa = mmu_uvtop(va);

	if (pa) return pa;

	return pmap_extract_internal(pmap, va);
}