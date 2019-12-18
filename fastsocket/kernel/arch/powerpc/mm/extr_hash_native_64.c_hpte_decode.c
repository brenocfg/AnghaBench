#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct hash_pte {unsigned long r; unsigned long v; } ;
struct TYPE_2__ {int shift; int penc; int avpnm; } ;

/* Variables and functions */
 unsigned long HPTES_PER_GROUP ; 
 int HPTE_V_AVPN_VAL (unsigned long) ; 
 unsigned long HPTE_V_LARGE ; 
 unsigned long HPTE_V_SECONDARY ; 
 unsigned long HPTE_V_SSIZE_SHIFT ; 
 int LP_BITS ; 
 unsigned long LP_MASK (int) ; 
 unsigned long LP_SHIFT ; 
 int MMU_PAGE_4K ; 
 int MMU_PAGE_COUNT ; 
#define  MMU_SEGSIZE_1T 129 
#define  MMU_SEGSIZE_256M 128 
 unsigned long htab_hash_mask ; 
 TYPE_1__* mmu_psize_defs ; 

__attribute__((used)) static void hpte_decode(struct hash_pte *hpte, unsigned long slot,
			int *psize, int *ssize, unsigned long *va)
{
	unsigned long hpte_r = hpte->r;
	unsigned long hpte_v = hpte->v;
	unsigned long avpn;
	int i, size, shift, penc;

	if (!(hpte_v & HPTE_V_LARGE))
		size = MMU_PAGE_4K;
	else {
		for (i = 0; i < LP_BITS; i++) {
			if ((hpte_r & LP_MASK(i+1)) == LP_MASK(i+1))
				break;
		}
		penc = LP_MASK(i+1) >> LP_SHIFT;
		for (size = 0; size < MMU_PAGE_COUNT; size++) {

			/* 4K pages are not represented by LP */
			if (size == MMU_PAGE_4K)
				continue;

			/* valid entries have a shift value */
			if (!mmu_psize_defs[size].shift)
				continue;

			if (penc == mmu_psize_defs[size].penc)
				break;
		}
	}

	/* This works for all page sizes, and for 256M and 1T segments */
	shift = mmu_psize_defs[size].shift;
	avpn = (HPTE_V_AVPN_VAL(hpte_v) & ~mmu_psize_defs[size].avpnm) << 23;

	if (shift < 23) {
		unsigned long vpi, vsid, pteg;

		pteg = slot / HPTES_PER_GROUP;
		if (hpte_v & HPTE_V_SECONDARY)
			pteg = ~pteg;
		switch (hpte_v >> HPTE_V_SSIZE_SHIFT) {
		case MMU_SEGSIZE_256M:
			vpi = ((avpn >> 28) ^ pteg) & htab_hash_mask;
			break;
		case MMU_SEGSIZE_1T:
			vsid = avpn >> 40;
			vpi = (vsid ^ (vsid << 25) ^ pteg) & htab_hash_mask;
			break;
		default:
			avpn = vpi = size = 0;
		}
		avpn |= (vpi << mmu_psize_defs[size].shift);
	}

	*va = avpn;
	*psize = size;
	*ssize = hpte_v >> HPTE_V_SSIZE_SHIFT;
}