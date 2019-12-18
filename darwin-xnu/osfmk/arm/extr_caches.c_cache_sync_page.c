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
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  int /*<<< orphan*/  ppnum_t ;
typedef  int /*<<< orphan*/  pmap_paddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  CleanPoU_DcacheRegion (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FlushPoC_Dcache () ; 
 int /*<<< orphan*/  InvalidatePoU_Icache () ; 
 int /*<<< orphan*/  InvalidatePoU_IcacheRegion (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 scalar_t__ isphysmem (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phystokv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptoa (int /*<<< orphan*/ ) ; 

void
cache_sync_page(
	ppnum_t pp
)
{
        pmap_paddr_t    paddr = ptoa(pp);

	if (isphysmem(paddr)) {
		vm_offset_t     vaddr = phystokv(paddr);

		CleanPoU_DcacheRegion(vaddr, PAGE_SIZE);
#ifdef  __ARM_IC_NOALIAS_ICACHE__
		InvalidatePoU_IcacheRegion(vaddr, PAGE_SIZE);
#else
		InvalidatePoU_Icache();
#endif
	} else {
		FlushPoC_Dcache();
		InvalidatePoU_Icache();
	};
}