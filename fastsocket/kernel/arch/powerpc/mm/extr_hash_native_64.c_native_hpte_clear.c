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
 unsigned long HPTES_PER_GROUP ; 
 unsigned long HPTE_V_VALID ; 
 int /*<<< orphan*/  __tlbie (unsigned long,int,int) ; 
 int /*<<< orphan*/  hpte_decode (struct hash_pte*,unsigned long,int*,int*,unsigned long*) ; 
 struct hash_pte* htab_address ; 
 int htab_hash_mask ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  native_tlbie_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void native_hpte_clear(void)
{
	unsigned long slot, slots, flags;
	struct hash_pte *hptep = htab_address;
	unsigned long hpte_v, va;
	unsigned long pteg_count;
	int psize, ssize;

	pteg_count = htab_hash_mask + 1;

	local_irq_save(flags);

	/* we take the tlbie lock and hold it.  Some hardware will
	 * deadlock if we try to tlbie from two processors at once.
	 */
	spin_lock(&native_tlbie_lock);

	slots = pteg_count * HPTES_PER_GROUP;

	for (slot = 0; slot < slots; slot++, hptep++) {
		/*
		 * we could lock the pte here, but we are the only cpu
		 * running,  right?  and for crash dump, we probably
		 * don't want to wait for a maybe bad cpu.
		 */
		hpte_v = hptep->v;

		/*
		 * Call __tlbie() here rather than tlbie() since we
		 * already hold the native_tlbie_lock.
		 */
		if (hpte_v & HPTE_V_VALID) {
			hpte_decode(hptep, slot, &psize, &ssize, &va);
			hptep->v = 0;
			__tlbie(va, psize, ssize);
		}
	}

	asm volatile("eieio; tlbsync; ptesync":::"memory");
	spin_unlock(&native_tlbie_lock);
	local_irq_restore(flags);
}