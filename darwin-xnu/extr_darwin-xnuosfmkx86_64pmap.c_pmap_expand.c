#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vm_page_t ;
typedef  int vm_object_offset_t ;
typedef  int /*<<< orphan*/  vm_map_offset_t ;
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  pt_entry_t ;
typedef  int /*<<< orphan*/  ppnum_t ;
typedef  TYPE_1__* pmap_t ;
typedef  int /*<<< orphan*/  pmap_paddr_t ;
typedef  scalar_t__ kern_return_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_14__ {int /*<<< orphan*/  pm_obj; } ;

/* Variables and functions */
 int INTEL_EPT_EX ; 
 int INTEL_PTE_USER ; 
 int /*<<< orphan*/  KERNEL_BASEMENT ; 
 scalar_t__ KERN_RESOURCE_SHORTAGE ; 
 scalar_t__ KERN_SUCCESS ; 
 int /*<<< orphan*/  OSAddAtomic (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OSAddAtomic64 (int,int /*<<< orphan*/ *) ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/ * PD_ENTRY_NULL ; 
 unsigned int PMAP_EXPAND_OPTIONS_ALIASMAP ; 
 unsigned int PMAP_EXPAND_OPTIONS_NOWAIT ; 
 int /*<<< orphan*/  PMAP_LOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  PMAP_UNLOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  PMAP_ZINFO_PALLOC (TYPE_1__*,int) ; 
 int /*<<< orphan*/  PMAP_ZINFO_PFREE (TYPE_1__*,int) ; 
 int PTE_READ (scalar_t__) ; 
 int PTE_WRITE (scalar_t__) ; 
 scalar_t__ PT_ENTRY_NULL ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  VM_KERN_MEMORY_PTE ; 
 int /*<<< orphan*/  VM_MAX_KERNEL_ADDRESS ; 
 int /*<<< orphan*/  VM_PAGE_FREE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VM_PAGE_GET_PHYS_PAGE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VM_PAGE_NULL ; 
 int /*<<< orphan*/  VM_PAGE_WAIT () ; 
 scalar_t__ __improbable (int) ; 
 int /*<<< orphan*/  alloc_ptepages_count ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  i386_ptob (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inuse_ptepages_count ; 
 scalar_t__ is_ept_pmap (TYPE_1__*) ; 
 TYPE_1__* kernel_pmap ; 
 int pa_to_pte (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ pdeidx (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pmap64_pde (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ pmap_expand_pdpt (TYPE_1__*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/ * pmap_pde (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ pmap_pte (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmap_store_pte (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pmap_zero_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_object_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_object_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_page_grab () ; 
 int /*<<< orphan*/  vm_page_insert_wired (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_page_lockspin_queues () ; 
 int /*<<< orphan*/  vm_page_unlock_queues () ; 
 int /*<<< orphan*/  vm_page_wire (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

kern_return_t
pmap_expand(
	pmap_t		map,
	vm_map_offset_t	vaddr,
	unsigned int options)
{
	pt_entry_t		*pdp;
	vm_page_t		m;
	pmap_paddr_t		pa;
	uint64_t		i;
	ppnum_t                 pn;
	boolean_t		is_ept = is_ept_pmap(map);


	/*
 	 * For the kernel, the virtual address must be in or above the basement
	 * which is for kexts and is in the 512GB immediately below the kernel..
	 * XXX - should use VM_MIN_KERNEL_AND_KEXT_ADDRESS not KERNEL_BASEMENT
	 */
	if (__improbable(map == kernel_pmap && 
		!(vaddr >= KERNEL_BASEMENT && vaddr <= VM_MAX_KERNEL_ADDRESS))) {
		if ((options & PMAP_EXPAND_OPTIONS_ALIASMAP) == 0) {
			panic("pmap_expand: bad vaddr 0x%llx for kernel pmap", vaddr);
		}
	}


	while ((pdp = pmap64_pde(map, vaddr)) == PD_ENTRY_NULL) {
		assert((options & PMAP_EXPAND_OPTIONS_ALIASMAP) == 0);
		kern_return_t pepkr = pmap_expand_pdpt(map, vaddr, options);
		if (pepkr != KERN_SUCCESS)
			return pepkr;
	}

	/*
	 *	Allocate a VM page for the pde entries.
	 */
	while ((m = vm_page_grab()) == VM_PAGE_NULL) {
		if (options & PMAP_EXPAND_OPTIONS_NOWAIT)
			return KERN_RESOURCE_SHORTAGE;
		VM_PAGE_WAIT();
	}

	/*
	 *	put the page into the pmap's obj list so it
	 *	can be found later.
	 */
	pn = VM_PAGE_GET_PHYS_PAGE(m);
	pa = i386_ptob(pn);
	i = pdeidx(map, vaddr);

	/*
	 *	Zero the page.
	 */
	pmap_zero_page(pn);

	vm_page_lockspin_queues();
	vm_page_wire(m, VM_KERN_MEMORY_PTE, TRUE);
	vm_page_unlock_queues();

	OSAddAtomic(1,  &inuse_ptepages_count);
	OSAddAtomic64(1,  &alloc_ptepages_count);
	PMAP_ZINFO_PALLOC(map, PAGE_SIZE);

	/* Take the oject lock (mutex) before the PMAP_LOCK (spinlock) */
	vm_object_lock(map->pm_obj);

	PMAP_LOCK(map);

	/*
	 *	See if someone else expanded us first
	 */
	if (pmap_pte(map, vaddr) != PT_ENTRY_NULL) {
		PMAP_UNLOCK(map);
		vm_object_unlock(map->pm_obj);

		VM_PAGE_FREE(m);

		OSAddAtomic(-1,  &inuse_ptepages_count);//todo replace all with inlines
		PMAP_ZINFO_PFREE(map, PAGE_SIZE);
		return KERN_SUCCESS;
	}

#if 0 /* DEBUG */
       if (0 != vm_page_lookup(map->pm_obj, (vm_object_offset_t)i * PAGE_SIZE)) {
	       panic("pmap_expand: obj not empty, pmap 0x%x pm_obj 0x%x vaddr 0x%llx i 0x%llx\n",
		     map, map->pm_obj, vaddr, i);
       }
#endif
	vm_page_insert_wired(m, map->pm_obj, (vm_object_offset_t)i * PAGE_SIZE, VM_KERN_MEMORY_PTE);
	vm_object_unlock(map->pm_obj);

	/*
	 *	Set the page directory entry for this page table.
	 */
	pdp = pmap_pde(map, vaddr);
	pmap_store_pte(pdp, pa_to_pte(pa)
				| PTE_READ(is_ept)
				| (is_ept ? INTEL_EPT_EX : INTEL_PTE_USER)
				| PTE_WRITE(is_ept));

	PMAP_UNLOCK(map);

	return KERN_SUCCESS;
}