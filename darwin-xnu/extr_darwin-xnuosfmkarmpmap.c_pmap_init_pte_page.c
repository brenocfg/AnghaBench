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
typedef  int /*<<< orphan*/  pt_entry_t ;
typedef  int /*<<< orphan*/  pt_desc_t ;
typedef  int /*<<< orphan*/  pmap_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  ARM_PGBYTES ; 
 int /*<<< orphan*/  DMB_ISHST ; 
 int /*<<< orphan*/  PVH_TYPE_NULL ; 
 int /*<<< orphan*/  PVH_TYPE_PTDP ; 
 int /*<<< orphan*/  __builtin_arm_dmb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ml_static_vtop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pa_index (int /*<<< orphan*/ ) ; 
 scalar_t__ pai_to_pvh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ptd_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptd_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ *) ; 
 scalar_t__ pvh_list (int /*<<< orphan*/ *) ; 
 scalar_t__ pvh_test_type (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pvh_update_head_unlocked (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
pmap_init_pte_page(
	pmap_t pmap,
	pt_entry_t *pte_p,
	vm_offset_t va,
	unsigned int ttlevel,
	boolean_t alloc_ptd)
{
	pt_desc_t   *ptdp = NULL;
	vm_offset_t *pvh;

	pvh = (vm_offset_t *)(pai_to_pvh(pa_index(ml_static_vtop((vm_offset_t)pte_p))));

	if (pvh_test_type(pvh, PVH_TYPE_NULL)) {
		if (alloc_ptd) {
			/*
			 * This path should only be invoked from arm_vm_init.  If we are emulating 16KB pages
			 * on 4KB hardware, we may already have allocated a page table descriptor for a
			 * bootstrap request, so we check for an existing PTD here.
			 */
			ptdp = ptd_alloc(pmap);
			pvh_update_head_unlocked(pvh, ptdp, PVH_TYPE_PTDP);
		} else {
			panic("pmap_init_pte_page(): pte_p %p", pte_p);
		}
	} else if (pvh_test_type(pvh, PVH_TYPE_PTDP)) {
		ptdp = (pt_desc_t*)(pvh_list(pvh));
	} else {
		panic("pmap_init_pte_page(): invalid PVH type for pte_p %p", pte_p);
	}

	bzero(pte_p, ARM_PGBYTES);
	// below barrier ensures the page zeroing is visible to PTW before
	// it is linked to the PTE of previous level
	__builtin_arm_dmb(DMB_ISHST);
	ptd_init(ptdp, pmap, va, ttlevel, pte_p);
}