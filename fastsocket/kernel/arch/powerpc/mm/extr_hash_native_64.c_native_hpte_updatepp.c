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
 int /*<<< orphan*/  DBG_LOW (char*,...) ; 
 unsigned long HPTE_R_C ; 
 unsigned long HPTE_R_N ; 
 unsigned long HPTE_R_PP ; 
 unsigned long HPTE_V_AVPN ; 
 int /*<<< orphan*/  HPTE_V_COMPARE (unsigned long,unsigned long) ; 
 unsigned long HPTE_V_VALID ; 
 unsigned long hpte_encode_v (unsigned long,int,int) ; 
 struct hash_pte* htab_address ; 
 int /*<<< orphan*/  native_lock_hpte (struct hash_pte*) ; 
 int /*<<< orphan*/  native_unlock_hpte (struct hash_pte*) ; 
 int /*<<< orphan*/  tlbie (unsigned long,int,int,int) ; 

__attribute__((used)) static long native_hpte_updatepp(unsigned long slot, unsigned long newpp,
				 unsigned long va, int psize, int ssize,
				 int local)
{
	struct hash_pte *hptep = htab_address + slot;
	unsigned long hpte_v, want_v;
	int ret = 0;

	want_v = hpte_encode_v(va, psize, ssize);

	DBG_LOW("    update(va=%016lx, avpnv=%016lx, hash=%016lx, newpp=%x)",
		va, want_v & HPTE_V_AVPN, slot, newpp);

	native_lock_hpte(hptep);

	hpte_v = hptep->v;

	/* Even if we miss, we need to invalidate the TLB */
	if (!HPTE_V_COMPARE(hpte_v, want_v) || !(hpte_v & HPTE_V_VALID)) {
		DBG_LOW(" -> miss\n");
		ret = -1;
	} else {
		DBG_LOW(" -> hit\n");
		/* Update the HPTE */
		hptep->r = (hptep->r & ~(HPTE_R_PP | HPTE_R_N)) |
			(newpp & (HPTE_R_PP | HPTE_R_N | HPTE_R_C));
	}
	native_unlock_hpte(hptep);

	/* Ensure it is out of the tlb too. */
	tlbie(va, psize, ssize, local);

	return ret;
}