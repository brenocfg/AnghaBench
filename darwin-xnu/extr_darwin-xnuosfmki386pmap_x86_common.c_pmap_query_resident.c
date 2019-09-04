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
typedef  scalar_t__ uint64_t ;
typedef  int pt_entry_t ;
typedef  scalar_t__ pmap_t ;
typedef  scalar_t__ mach_vm_size_t ;
typedef  int /*<<< orphan*/  boolean_t ;
typedef  int addr64_t ;

/* Variables and functions */
 int DBG_FUNC_END ; 
 int DBG_FUNC_START ; 
 scalar_t__ PAGE_SIZE ; 
 int PMAP_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PMAP_LOCK (scalar_t__) ; 
 scalar_t__ PMAP_NULL ; 
 int /*<<< orphan*/  PMAP_TRACE (int,scalar_t__,...) ; 
 int /*<<< orphan*/  PMAP_UNLOCK (scalar_t__) ; 
 int /*<<< orphan*/  PMAP__QUERY_RESIDENT ; 
 int PTE_COMPRESSED ; 
 int PTE_PS ; 
 int PTE_VALID_MASK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VM_KERNEL_ADDRHIDE (int) ; 
 size_t intel_btop (int) ; 
 int /*<<< orphan*/  is_ept_pmap (scalar_t__) ; 
 scalar_t__ kernel_pmap ; 
 scalar_t__ max_preemption_latency_tsc ; 
 int pde_mapped_size ; 
 int /*<<< orphan*/  pmap_intr_assert () ; 
 int* pmap_pde (scalar_t__,int) ; 
 int* pmap_pte (scalar_t__,int) ; 
 scalar_t__ pte_to_pa (int) ; 
 size_t ptenum (int) ; 
 scalar_t__ rdtsc64 () ; 

mach_vm_size_t
pmap_query_resident(
	pmap_t		pmap,
	addr64_t	s64,
	addr64_t	e64,
	mach_vm_size_t	*compressed_bytes_p)
{
	pt_entry_t     *pde;
	pt_entry_t     *spte, *epte;
	addr64_t        l64;
	uint64_t        deadline;
	mach_vm_size_t	resident_bytes;
	mach_vm_size_t	compressed_bytes;
	boolean_t	is_ept;

	pmap_intr_assert();

	if (pmap == PMAP_NULL || pmap == kernel_pmap || s64 == e64) {
		if (compressed_bytes_p) {
			*compressed_bytes_p = 0;
		}
		return 0;
	}

	is_ept = is_ept_pmap(pmap);

	PMAP_TRACE(PMAP_CODE(PMAP__QUERY_RESIDENT) | DBG_FUNC_START,
	           VM_KERNEL_ADDRHIDE(pmap), VM_KERNEL_ADDRHIDE(s64),
	           VM_KERNEL_ADDRHIDE(e64));

	resident_bytes = 0;
	compressed_bytes = 0;

	PMAP_LOCK(pmap);

	deadline = rdtsc64() + max_preemption_latency_tsc;

	while (s64 < e64) {
		l64 = (s64 + pde_mapped_size) & ~(pde_mapped_size - 1);
		if (l64 > e64)
			l64 = e64;
		pde = pmap_pde(pmap, s64);

		if (pde && (*pde & PTE_VALID_MASK(is_ept))) {
			if (*pde & PTE_PS) {
				/* superpage: not supported */
			} else {
				spte = pmap_pte(pmap,
						(s64 & ~(pde_mapped_size - 1)));
				spte = &spte[ptenum(s64)];
				epte = &spte[intel_btop(l64 - s64)];

				for (; spte < epte; spte++) {
					if (pte_to_pa(*spte) != 0) {
						resident_bytes += PAGE_SIZE;
					} else if (*spte & PTE_COMPRESSED) {
						compressed_bytes += PAGE_SIZE;
					}
				}

			}
		}
		s64 = l64;

		if (s64 < e64 && rdtsc64() >= deadline) {
			PMAP_UNLOCK(pmap);
			PMAP_LOCK(pmap);
			deadline = rdtsc64() + max_preemption_latency_tsc;
		}
	}

	PMAP_UNLOCK(pmap);

	PMAP_TRACE(PMAP_CODE(PMAP__QUERY_RESIDENT) | DBG_FUNC_END,
	           resident_bytes);

	if (compressed_bytes_p) {
		*compressed_bytes_p = compressed_bytes;
	}
	return resident_bytes;
}