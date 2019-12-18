#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_8__ ;
typedef  struct TYPE_12__   TYPE_7__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  scalar_t__ pml4_entry_t ;
typedef  TYPE_1__* pmap_t ;
typedef  size_t pmap_paddr_t ;
typedef  size_t pcid_t ;
struct TYPE_11__ {TYPE_1__** cpu_pcid_last_pmap_dispatched; } ;
typedef  TYPE_2__ pcid_cdata_t ;
typedef  int boolean_t ;
struct TYPE_13__ {int cpu_pmap_pcid_enabled; size_t cpu_last_pcid; size_t cpu_active_pcid; size_t cpu_kernel_pcid; size_t cpu_pcid_last_cr3; int cpu_ucr3; scalar_t__* cpu_pmap_pcid_coherentp; TYPE_2__* cpu_pcid_data; } ;
struct TYPE_12__ {int cpu_ucr3; size_t cpu_task_cr3; } ;
struct TYPE_10__ {size_t* pmap_pcid_cpus; scalar_t__* pmap_pcid_coherency_vector; size_t pm_cr3; scalar_t__* pm_pml4; int pm_ucr3; } ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  KERNEL_DEBUG_CONSTANT (int,TYPE_1__*,size_t,int,int,int /*<<< orphan*/ ) ; 
 size_t KERNEL_PML4_INDEX ; 
 int PCID_RECORD_SIZE ; 
 size_t PMAP_PCID_INVALID_PCID ; 
 size_t PMAP_PCID_MAX_PCID ; 
 int TRUE ; 
 scalar_t__ __improbable (int) ; 
 scalar_t__ __probable (int) ; 
 TYPE_8__* cpu_datap (int) ; 
 TYPE_7__* cpu_shadowp (int) ; 
 TYPE_1__* kernel_pmap ; 
 int /*<<< orphan*/  npz ; 
 size_t* pcid_record_array ; 
 scalar_t__* pmap64_pml4 (TYPE_1__*,unsigned long long) ; 
 int /*<<< orphan*/  pmap_assert (int) ; 
 size_t pmap_pcid_allocate_pcid (int) ; 
 int /*<<< orphan*/  pmap_pcid_validate_cpu (TYPE_1__*,int) ; 
 int /*<<< orphan*/  set_cr3_composed (size_t,size_t,int) ; 

void	pmap_pcid_activate(pmap_t tpmap, int ccpu, boolean_t nopagezero, boolean_t copyio) {
	pcid_t		new_pcid = tpmap->pmap_pcid_cpus[ccpu];
	pmap_t		last_pmap;
	boolean_t	pcid_conflict = FALSE, pending_flush = FALSE;
	pcid_cdata_t	*pcdata = cpu_datap(ccpu)->cpu_pcid_data;

	pmap_assert(cpu_datap(ccpu)->cpu_pmap_pcid_enabled);
	if (__improbable(new_pcid == PMAP_PCID_INVALID_PCID)) {
		new_pcid = tpmap->pmap_pcid_cpus[ccpu] = pmap_pcid_allocate_pcid(ccpu);
	}

	pmap_assert(new_pcid != PMAP_PCID_INVALID_PCID);
#ifdef	PCID_ASSERT
	cpu_datap(ccpu)->cpu_last_pcid = cpu_datap(ccpu)->cpu_active_pcid;
#endif
	cpu_datap(ccpu)->cpu_active_pcid = new_pcid;

	pending_flush = (tpmap->pmap_pcid_coherency_vector[ccpu] != 0);
	if (__probable(pending_flush == FALSE)) {
		last_pmap = pcdata->cpu_pcid_last_pmap_dispatched[new_pcid];
		pcid_conflict = ((last_pmap != NULL) && (tpmap != last_pmap));
	}
	if (__improbable(pending_flush || pcid_conflict)) {
		pmap_pcid_validate_cpu(tpmap, ccpu);
	}
	/* Consider making this a unique id */
	pcdata->cpu_pcid_last_pmap_dispatched[new_pcid] = tpmap;

	pmap_assert(new_pcid < PMAP_PCID_MAX_PCID);
	pmap_assert(((tpmap ==  kernel_pmap) && new_pcid == 0) ||
	    ((new_pcid != PMAP_PCID_INVALID_PCID) && (new_pcid != 0)));
#if	PMAP_ASSERT
	pcid_record_array[ccpu % PCID_RECORD_SIZE] = tpmap->pm_cr3 | new_pcid | (((uint64_t)(!(pending_flush || pcid_conflict))) <<63);
	pml4_entry_t *pml4 = pmap64_pml4(tpmap, 0ULL);
	/* Diagnostic to detect pagetable anchor corruption */
	if (pml4[KERNEL_PML4_INDEX] != kernel_pmap->pm_pml4[KERNEL_PML4_INDEX])
		__asm__ volatile("int3");
#endif	/* PMAP_ASSERT */

	pmap_paddr_t ncr3 = tpmap->pm_cr3;

	if (__improbable(nopagezero)) {
		pending_flush = TRUE;
		if (copyio == FALSE) {
			new_pcid = kernel_pmap->pmap_pcid_cpus[ccpu];
			ncr3 = kernel_pmap->pm_cr3;
		}
		cpu_datap(ccpu)->cpu_kernel_pcid = kernel_pmap->pmap_pcid_cpus[ccpu];
		npz++;
	}

	uint64_t preserve = !(pending_flush || pcid_conflict);
	set_cr3_composed(ncr3, new_pcid, preserve);
#if DEBUG
	cpu_datap(ccpu)->cpu_pcid_last_cr3 = ncr3 | new_pcid | preserve << 63;
#endif
	uint64_t spcid = (new_pcid + PMAP_PCID_MAX_PCID);
	if (new_pcid == 0) {
		spcid = 0;
	}
	uint64_t scr3 = tpmap->pm_ucr3 | spcid;

	cpu_datap(ccpu)->cpu_ucr3 = scr3;
	cpu_shadowp(ccpu)->cpu_ucr3 = scr3;

	cpu_shadowp(ccpu)->cpu_task_cr3 = ncr3 | new_pcid;

	if (!pending_flush) {
		/* We did not previously observe a pending invalidation for this
		 * ASID. However, the load from the coherency vector
		 * could've been reordered ahead of the store to the
		 * active_cr3 field (in the context switch path, our
		 * caller). Re-consult the pending invalidation vector
		 * after the CR3 write. We rely on MOV CR3's documented
		 * serializing property to avoid insertion of an expensive
		 * barrier. (DRK)
		 */
		pending_flush = (tpmap->pmap_pcid_coherency_vector[ccpu] != 0);
		if (__improbable(pending_flush != 0)) {
			pmap_pcid_validate_cpu(tpmap, ccpu);
			set_cr3_composed(ncr3, new_pcid, FALSE);
		}
	}
	cpu_datap(ccpu)->cpu_pmap_pcid_coherentp = &(tpmap->pmap_pcid_coherency_vector[ccpu]);
#if	DEBUG	
	KERNEL_DEBUG_CONSTANT(0x9c1d0000, tpmap, new_pcid, pending_flush, pcid_conflict, 0);
#endif
}