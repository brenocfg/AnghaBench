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
typedef  int /*<<< orphan*/  ppnum_t ;
typedef  scalar_t__ pmap_t ;
typedef  int pmap_paddr_t ;
typedef  int /*<<< orphan*/  addr64_t ;
struct TYPE_2__ {scalar_t__ map; } ;

/* Variables and functions */
 int PAGE_SHIFT ; 
 TYPE_1__* current_thread () ; 
 scalar_t__ kernel_pmap ; 
 int mmu_kvtop (int /*<<< orphan*/ ) ; 
 int mmu_uvtop (int /*<<< orphan*/ ) ; 
 scalar_t__ not_in_kdp ; 
 int /*<<< orphan*/  pmap_find_phys_internal (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmap_vtophys (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ vm_map_pmap (scalar_t__) ; 

ppnum_t
pmap_find_phys(
	pmap_t pmap,
	addr64_t va)
{
	pmap_paddr_t	pa=0;

	if (pmap == kernel_pmap)
		pa = mmu_kvtop(va);
	else if ((current_thread()->map) && (pmap == vm_map_pmap(current_thread()->map)))
		pa = mmu_uvtop(va);

	if (pa) return (ppnum_t)(pa >> PAGE_SHIFT);

	if (not_in_kdp) {
		return pmap_find_phys_internal(pmap, va);
	} else {
		return pmap_vtophys(pmap, va);
	}
}