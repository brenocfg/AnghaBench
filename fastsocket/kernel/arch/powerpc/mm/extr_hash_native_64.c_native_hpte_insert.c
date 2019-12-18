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
struct hash_pte {unsigned long v; unsigned long r; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_LOW (char*,int,unsigned long,unsigned long,...) ; 
 int HPTES_PER_GROUP ; 
 unsigned long HPTE_V_BOLTED ; 
 unsigned long HPTE_V_SECONDARY ; 
 unsigned long HPTE_V_VALID ; 
 int /*<<< orphan*/  eieio () ; 
 unsigned long hpte_encode_r (unsigned long,int) ; 
 unsigned long hpte_encode_v (unsigned long,int,int) ; 
 struct hash_pte* htab_address ; 
 int /*<<< orphan*/  native_lock_hpte (struct hash_pte*) ; 
 int /*<<< orphan*/  native_unlock_hpte (struct hash_pte*) ; 

__attribute__((used)) static long native_hpte_insert(unsigned long hpte_group, unsigned long va,
			unsigned long pa, unsigned long rflags,
			unsigned long vflags, int psize, int ssize)
{
	struct hash_pte *hptep = htab_address + hpte_group;
	unsigned long hpte_v, hpte_r;
	int i;

	if (!(vflags & HPTE_V_BOLTED)) {
		DBG_LOW("    insert(group=%lx, va=%016lx, pa=%016lx,"
			" rflags=%lx, vflags=%lx, psize=%d)\n",
			hpte_group, va, pa, rflags, vflags, psize);
	}

	for (i = 0; i < HPTES_PER_GROUP; i++) {
		if (! (hptep->v & HPTE_V_VALID)) {
			/* retry with lock held */
			native_lock_hpte(hptep);
			if (! (hptep->v & HPTE_V_VALID))
				break;
			native_unlock_hpte(hptep);
		}

		hptep++;
	}

	if (i == HPTES_PER_GROUP)
		return -1;

	hpte_v = hpte_encode_v(va, psize, ssize) | vflags | HPTE_V_VALID;
	hpte_r = hpte_encode_r(pa, psize) | rflags;

	if (!(vflags & HPTE_V_BOLTED)) {
		DBG_LOW(" i=%x hpte_v=%016lx, hpte_r=%016lx\n",
			i, hpte_v, hpte_r);
	}

	hptep->r = hpte_r;
	/* Guarantee the second dword is visible before the valid bit */
	eieio();
	/*
	 * Now set the first dword including the valid bit
	 * NOTE: this also unlocks the hpte
	 */
	hptep->v = hpte_v;

	__asm__ __volatile__ ("ptesync" : : : "memory");

	return i | (!!(vflags & HPTE_V_SECONDARY) << 3);
}