#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_9__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* pmap_t ;
struct TYPE_19__ {TYPE_1__* map; } ;
struct TYPE_18__ {scalar_t__ resident_page_count; } ;
struct TYPE_17__ {int ref_count; int /*<<< orphan*/  ledger; TYPE_4__* pm_obj; TYPE_4__* pm_obj_pdpt; TYPE_4__* pm_obj_pml4; struct TYPE_17__* pm_upml4; struct TYPE_17__* pm_pml4; } ;
struct TYPE_16__ {TYPE_2__* pmap; } ;

/* Variables and functions */
 int DBG_FUNC_END ; 
 int DBG_FUNC_START ; 
 int /*<<< orphan*/  OSAddAtomic (int,int /*<<< orphan*/ *) ; 
 int PAGE_SIZE ; 
 int PMAP_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PMAP_LOCK (TYPE_2__*) ; 
 TYPE_2__* PMAP_NULL ; 
 int /*<<< orphan*/  PMAP_TRACE (int,...) ; 
 int /*<<< orphan*/  PMAP_UNLOCK (TYPE_2__*) ; 
 int /*<<< orphan*/  PMAP_UPDATE_TLBS (TYPE_2__*,int,int) ; 
 int /*<<< orphan*/  PMAP_ZINFO_PFREE (TYPE_2__*,int) ; 
 int /*<<< orphan*/  PMAP__DESTROY ; 
 int TRUE ; 
 int /*<<< orphan*/  VM_KERNEL_ADDRHIDe (TYPE_2__*) ; 
 TYPE_9__* current_thread () ; 
 int /*<<< orphan*/  inuse_ptepages_count ; 
 TYPE_2__* kernel_pmap ; 
 int /*<<< orphan*/  ledger_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmap_anchor_zone ; 
 int /*<<< orphan*/  pmap_assert (int) ; 
 int /*<<< orphan*/  pmap_check_ledgers (TYPE_2__*) ; 
 int /*<<< orphan*/  pmap_destroy_pcid_sync (TYPE_2__*) ; 
 scalar_t__ pmap_pcid_ncpus ; 
 int /*<<< orphan*/  pmap_uanchor_zone ; 
 int /*<<< orphan*/  pmap_zone ; 
 int /*<<< orphan*/  vm_object_deallocate (TYPE_4__*) ; 
 int /*<<< orphan*/  zfree (int /*<<< orphan*/ ,TYPE_2__*) ; 

void
pmap_destroy(pmap_t	p)
{
	int		c;

	if (p == PMAP_NULL)
		return;

	PMAP_TRACE(PMAP_CODE(PMAP__DESTROY) | DBG_FUNC_START,
	           VM_KERNEL_ADDRHIDe(p));

	PMAP_LOCK(p);

	c = --p->ref_count;

	pmap_assert((current_thread() && (current_thread()->map)) ? (current_thread()->map->pmap != p) : TRUE);

	if (c == 0) {
		/* 
		 * If some cpu is not using the physical pmap pointer that it
		 * is supposed to be (see set_dirbase), we might be using the
		 * pmap that is being destroyed! Make sure we are
		 * physically on the right pmap:
		 */
		PMAP_UPDATE_TLBS(p, 0x0ULL, 0xFFFFFFFFFFFFF000ULL);
		if (pmap_pcid_ncpus)
			pmap_destroy_pcid_sync(p);
	}

	PMAP_UNLOCK(p);

	if (c != 0) {
		PMAP_TRACE(PMAP_CODE(PMAP__DESTROY) | DBG_FUNC_END);
		pmap_assert(p == kernel_pmap);
	        return;	/* still in use */
	}

	/*
	 *	Free the memory maps, then the
	 *	pmap structure.
	 */
	int inuse_ptepages = 0;

	zfree(pmap_anchor_zone, p->pm_pml4);
	zfree(pmap_uanchor_zone, p->pm_upml4);

	inuse_ptepages += p->pm_obj_pml4->resident_page_count;
	vm_object_deallocate(p->pm_obj_pml4);

	inuse_ptepages += p->pm_obj_pdpt->resident_page_count;
	vm_object_deallocate(p->pm_obj_pdpt);

	inuse_ptepages += p->pm_obj->resident_page_count;
	vm_object_deallocate(p->pm_obj);

	OSAddAtomic(-inuse_ptepages,  &inuse_ptepages_count);
	PMAP_ZINFO_PFREE(p, inuse_ptepages * PAGE_SIZE);

	pmap_check_ledgers(p);
	ledger_dereference(p->ledger);
	zfree(pmap_zone, p);

	PMAP_TRACE(PMAP_CODE(PMAP__DESTROY) | DBG_FUNC_END);
}