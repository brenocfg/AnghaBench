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
typedef  unsigned long u64 ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_LOW (char*,...) ; 
 unsigned long HPTE_V_BOLTED ; 
 unsigned long HPTE_V_SECONDARY ; 
 unsigned long HPTE_V_VALID ; 
 int /*<<< orphan*/  MMU_SEGSIZE_256M ; 
 unsigned long _PAGE_COHERENT ; 
 unsigned long _PAGE_NO_CACHE ; 
 int /*<<< orphan*/  beat_htab_lock ; 
 unsigned long beat_insert_htab_entry (int /*<<< orphan*/ ,unsigned long,unsigned long,unsigned long,unsigned long,unsigned long*) ; 
 unsigned long beat_read_mask (unsigned long) ; 
 unsigned long hpte_encode_r (unsigned long,int) ; 
 unsigned long hpte_encode_v (unsigned long,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static long beat_lpar_hpte_insert(unsigned long hpte_group,
				  unsigned long va, unsigned long pa,
				  unsigned long rflags, unsigned long vflags,
				  int psize, int ssize)
{
	unsigned long lpar_rc;
	u64 hpte_v, hpte_r, slot;

	/* same as iseries */
	if (vflags & HPTE_V_SECONDARY)
		return -1;

	if (!(vflags & HPTE_V_BOLTED))
		DBG_LOW("hpte_insert(group=%lx, va=%016lx, pa=%016lx, "
			"rflags=%lx, vflags=%lx, psize=%d)\n",
		hpte_group, va, pa, rflags, vflags, psize);

	hpte_v = hpte_encode_v(va, psize, MMU_SEGSIZE_256M) |
		vflags | HPTE_V_VALID;
	hpte_r = hpte_encode_r(pa, psize) | rflags;

	if (!(vflags & HPTE_V_BOLTED))
		DBG_LOW(" hpte_v=%016lx, hpte_r=%016lx\n", hpte_v, hpte_r);

	if (rflags & _PAGE_NO_CACHE)
		hpte_r &= ~_PAGE_COHERENT;

	spin_lock(&beat_htab_lock);
	lpar_rc = beat_read_mask(hpte_group);
	if (lpar_rc == 0) {
		if (!(vflags & HPTE_V_BOLTED))
			DBG_LOW(" full\n");
		spin_unlock(&beat_htab_lock);
		return -1;
	}

	lpar_rc = beat_insert_htab_entry(0, hpte_group, lpar_rc << 48,
		hpte_v, hpte_r, &slot);
	spin_unlock(&beat_htab_lock);

	/*
	 * Since we try and ioremap PHBs we don't own, the pte insert
	 * will fail. However we must catch the failure in hash_page
	 * or we will loop forever, so return -2 in this case.
	 */
	if (unlikely(lpar_rc != 0)) {
		if (!(vflags & HPTE_V_BOLTED))
			DBG_LOW(" lpar err %lx\n", lpar_rc);
		return -2;
	}
	if (!(vflags & HPTE_V_BOLTED))
		DBG_LOW(" -> slot: %lx\n", slot);

	/* We have to pass down the secondary bucket bit here as well */
	return (slot ^ hpte_group) & 15;
}