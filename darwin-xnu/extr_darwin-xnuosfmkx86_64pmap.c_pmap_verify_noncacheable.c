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
typedef  int pt_entry_t ;

/* Variables and functions */
 int INTEL_PTE_NCACHE ; 
 int INTEL_PTE_PTA ; 
 int /*<<< orphan*/  kernel_pmap ; 
 int /*<<< orphan*/  panic (char*,uintptr_t,...) ; 
 int* pmap_pte (int /*<<< orphan*/ ,uintptr_t) ; 

void pmap_verify_noncacheable(uintptr_t vaddr) {
	pt_entry_t *ptep = NULL;
	ptep = pmap_pte(kernel_pmap, vaddr);
	if (ptep == NULL) {
		panic("pmap_verify_noncacheable: no translation for 0x%lx", vaddr);
	}
	/* Non-cacheable OK */
	if (*ptep & (INTEL_PTE_NCACHE))
		return;
	/* Write-combined OK */
	if (*ptep & (INTEL_PTE_PTA))
		return;
	panic("pmap_verify_noncacheable: IO read from a cacheable address? address: 0x%lx, PTE: %p, *PTE: 0x%llx", vaddr, ptep, *ptep);
}