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
typedef  scalar_t__ vm_map_address_t ;
typedef  scalar_t__ pmap_t ;

/* Variables and functions */
 scalar_t__ ARM_TT_L2_OFFMASK ; 
 scalar_t__ ARM_TT_L2_SIZE ; 
 int DBG_FUNC_END ; 
 int DBG_FUNC_START ; 
 int PMAP_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ PMAP_NULL ; 
 int /*<<< orphan*/  PMAP_TRACE (int,int,...) ; 
 int /*<<< orphan*/  PMAP_UPDATE_TLBS (scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  PMAP__REMOVE ; 
 int /*<<< orphan*/  VM_KERNEL_ADDRHIDE (scalar_t__) ; 
 scalar_t__ pmap_remove_options_internal (scalar_t__,scalar_t__,scalar_t__,int) ; 

void
pmap_remove_options(
	pmap_t pmap,
	vm_map_address_t start,
	vm_map_address_t end,
	int options)
{
	int             remove_count = 0;
	vm_map_address_t va;

	if (pmap == PMAP_NULL)
		return;

	PMAP_TRACE(2, PMAP_CODE(PMAP__REMOVE) | DBG_FUNC_START,
	           VM_KERNEL_ADDRHIDE(pmap), VM_KERNEL_ADDRHIDE(start),
	           VM_KERNEL_ADDRHIDE(end));

#if MACH_ASSERT
	if ((start|end) & PAGE_MASK) {
		panic("pmap_remove_options() pmap %p start 0x%llx end 0x%llx\n",
		      pmap, (uint64_t)start, (uint64_t)end);
	}
	if ((end < start) || (start < pmap->min) || (end > pmap->max)) {
		panic("pmap_remove_options(): invalid address range, pmap=%p, start=0x%llx, end=0x%llx\n",
		      pmap, (uint64_t)start, (uint64_t)end);
	}
#endif

	/*
	 *      Invalidate the translation buffer first
	 */
	va = start;
	while (va < end) {
		vm_map_address_t l;

#if	(__ARM_VMSA__ == 7)
		l = ((va + ARM_TT_L1_SIZE) & ~ARM_TT_L1_OFFMASK);
#else
		l = ((va + ARM_TT_L2_SIZE) & ~ARM_TT_L2_OFFMASK);
#endif
		if (l > end)
			l = end;

		remove_count += pmap_remove_options_internal(pmap, va, l, options);

		va = l;
	}

	if (remove_count > 0)
		PMAP_UPDATE_TLBS(pmap, start, end);

	PMAP_TRACE(2, PMAP_CODE(PMAP__REMOVE) | DBG_FUNC_END);
}