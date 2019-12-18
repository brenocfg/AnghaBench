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
struct hash_pte {unsigned long v; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_LOW (char*,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  HPTE_V_COMPARE (unsigned long,unsigned long) ; 
 unsigned long HPTE_V_VALID ; 
 unsigned long hpte_encode_v (unsigned long,int,int) ; 
 struct hash_pte* htab_address ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  native_lock_hpte (struct hash_pte*) ; 
 int /*<<< orphan*/  native_unlock_hpte (struct hash_pte*) ; 
 int /*<<< orphan*/  tlbie (unsigned long,int,int,int) ; 

__attribute__((used)) static void native_hpte_invalidate(unsigned long slot, unsigned long va,
				   int psize, int ssize, int local)
{
	struct hash_pte *hptep = htab_address + slot;
	unsigned long hpte_v;
	unsigned long want_v;
	unsigned long flags;

	local_irq_save(flags);

	DBG_LOW("    invalidate(va=%016lx, hash: %x)\n", va, slot);

	want_v = hpte_encode_v(va, psize, ssize);
	native_lock_hpte(hptep);
	hpte_v = hptep->v;

	/* Even if we miss, we need to invalidate the TLB */
	if (!HPTE_V_COMPARE(hpte_v, want_v) || !(hpte_v & HPTE_V_VALID))
		native_unlock_hpte(hptep);
	else
		/* Invalidate the hpte. NOTE: this also unlocks it */
		hptep->v = 0;

	/* Invalidate the TLB */
	tlbie(va, psize, ssize, local);

	local_irq_restore(flags);
}