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
typedef  int pt_entry_t ;

/* Variables and functions */
 int AP_RONA ; 
 int ARM_PTE_AF ; 
 int ARM_PTE_ATTRINDX (int /*<<< orphan*/ ) ; 
 int ARM_PTE_EMPTY ; 
 int ARM_PTE_NX ; 
 int ARM_PTE_PNX ; 
 int ARM_PTE_SH ; 
 int ARM_PTE_TYPE ; 
 int /*<<< orphan*/  CACHE_ATTRINDX_WRITEBACK ; 
 int /*<<< orphan*/  FLUSH_PTE_RANGE (int*,int*) ; 
 scalar_t__ LOWGLOBAL_ALIAS ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  PMAP_UPDATE_TLBS (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int* PT_ENTRY_NULL ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  kernel_pmap ; 
 int /*<<< orphan*/  lowGlo ; 
 int /*<<< orphan*/  ml_static_vtop (int /*<<< orphan*/ ) ; 
 int pa_to_pte (int /*<<< orphan*/ ) ; 
 int* pmap_pte (int /*<<< orphan*/ ,scalar_t__) ; 

void
pmap_map_globals(
	void)
{
	pt_entry_t	*ptep, pte;

	ptep = pmap_pte(kernel_pmap, LOWGLOBAL_ALIAS);
	assert(ptep != PT_ENTRY_NULL);
	assert(*ptep == ARM_PTE_EMPTY);

	pte = pa_to_pte(ml_static_vtop((vm_offset_t)&lowGlo)) | AP_RONA | ARM_PTE_NX | ARM_PTE_PNX | ARM_PTE_AF | ARM_PTE_TYPE;
#if __ARM_KERNEL_PROTECT__
	pte |= ARM_PTE_NG;
#endif /* __ARM_KERNEL_PROTECT__ */
	pte |= ARM_PTE_ATTRINDX(CACHE_ATTRINDX_WRITEBACK);
#if	(__ARM_VMSA__ > 7)
	pte |= ARM_PTE_SH(SH_OUTER_MEMORY);
#else
	pte |= ARM_PTE_SH;
#endif
	*ptep = pte;
	FLUSH_PTE_RANGE(ptep,(ptep+1));
	PMAP_UPDATE_TLBS(kernel_pmap, LOWGLOBAL_ALIAS, LOWGLOBAL_ALIAS + PAGE_SIZE);
}