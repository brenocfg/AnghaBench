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
typedef  int vm_prot_t ;
typedef  scalar_t__ vm_offset_t ;
typedef  int vm_map_offset_t ;
typedef  int pt_entry_t ;

/* Variables and functions */
 int INTEL_PTE_MOD ; 
 int INTEL_PTE_NX ; 
 int INTEL_PTE_REF ; 
 int INTEL_PTE_VALID ; 
 int INTEL_PTE_WIRED ; 
 int INTEL_PTE_WRITE ; 
 int PAGE_MASK ; 
 scalar_t__ PAGE_SIZE ; 
 unsigned int PMAP_EXPAND_OPTIONS_ALIASMAP ; 
 int* PT_ENTRY_NULL ; 
 int VM_PROT_EXECUTE ; 
 int VM_PROT_WRITE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  kernel_pmap ; 
 int pa_to_pte (scalar_t__) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  pmap_expand (int /*<<< orphan*/ ,scalar_t__,unsigned int) ; 
 int* pmap_pte (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pmap_store_pte (int*,int) ; 
 scalar_t__ pte_to_pa (int) ; 

void
pmap_alias(
	vm_offset_t	ava,
	vm_map_offset_t	start_addr,
	vm_map_offset_t	end_addr,
	vm_prot_t	prot,
	unsigned int	eoptions)
{
	pt_entry_t	prot_template, template;
	pt_entry_t	*aptep, *sptep;

	prot_template =  INTEL_PTE_REF | INTEL_PTE_MOD | INTEL_PTE_WIRED | INTEL_PTE_VALID;
	if ((prot & VM_PROT_EXECUTE) == 0)
		prot_template |= INTEL_PTE_NX;

	if (prot & VM_PROT_WRITE)
		prot_template |= INTEL_PTE_WRITE;
	assert(((start_addr | end_addr) & PAGE_MASK) == 0);
	while (start_addr < end_addr) {
		aptep = pmap_pte(kernel_pmap, (vm_map_offset_t)ava);
		if (aptep == PT_ENTRY_NULL) {
			if (eoptions & PMAP_EXPAND_OPTIONS_ALIASMAP) {
				pmap_expand(kernel_pmap, ava, PMAP_EXPAND_OPTIONS_ALIASMAP);
				aptep = pmap_pte(kernel_pmap, (vm_map_offset_t)ava);
			} else {
				panic("pmap_alias: Invalid alias address");
			}
		}
		/* The aliased range should not have any active mappings */
		assert(pte_to_pa(*aptep) == 0);

		sptep = pmap_pte(kernel_pmap, start_addr);
		assert(sptep != PT_ENTRY_NULL && (pte_to_pa(*sptep) != 0));
		template = pa_to_pte(pte_to_pa(*sptep)) | prot_template;
		pmap_store_pte(aptep, template);

		ava += PAGE_SIZE;
		start_addr += PAGE_SIZE;
	}
}