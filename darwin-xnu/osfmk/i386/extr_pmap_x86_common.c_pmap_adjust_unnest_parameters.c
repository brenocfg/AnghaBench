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
typedef  int vm_map_offset_t ;
typedef  int /*<<< orphan*/  pmap_t ;
typedef  int pd_entry_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int INTEL_PDPTE_NESTED ; 
 int NBPDPT ; 
 int /*<<< orphan*/  PMAP_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PMAP_UNLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  cpu_64bit ; 
 int* pmap64_pdpt (int /*<<< orphan*/ ,int) ; 

boolean_t pmap_adjust_unnest_parameters(pmap_t p, vm_map_offset_t *s, vm_map_offset_t *e) {
	pd_entry_t *pdpte;
	boolean_t rval = FALSE;

	if (!cpu_64bit)
		return rval;

	PMAP_LOCK(p);

	pdpte = pmap64_pdpt(p, *s);
	if (pdpte && (*pdpte & INTEL_PDPTE_NESTED)) {
		*s &= ~(NBPDPT -1);
		rval = TRUE;
	}

	pdpte = pmap64_pdpt(p, *e);
	if (pdpte && (*pdpte & INTEL_PDPTE_NESTED)) {
		*e = ((*e + NBPDPT) & ~(NBPDPT -1));
		rval = TRUE;
	}

	PMAP_UNLOCK(p);

	return rval;
}