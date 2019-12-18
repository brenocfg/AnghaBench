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
typedef  int u64 ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  DBG_LOW (char*,...) ; 
 unsigned long HPTE_V_AVPN ; 
 int /*<<< orphan*/  MMU_SEGSIZE_256M ; 
 int /*<<< orphan*/  beat_htab_lock ; 
 int beat_lpar_hpte_getword0 (unsigned long) ; 
 unsigned long beat_write_htab_entry (int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ,int,int*,int*) ; 
 unsigned long hpte_encode_v (unsigned long,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static long beat_lpar_hpte_updatepp(unsigned long slot,
				    unsigned long newpp,
				    unsigned long va,
				    int psize, int ssize, int local)
{
	unsigned long lpar_rc;
	u64 dummy0, dummy1;
	unsigned long want_v;

	want_v = hpte_encode_v(va, psize, MMU_SEGSIZE_256M);

	DBG_LOW("    update: "
		"avpnv=%016lx, slot=%016lx, psize: %d, newpp %016lx ... ",
		want_v & HPTE_V_AVPN, slot, psize, newpp);

	spin_lock(&beat_htab_lock);
	dummy0 = beat_lpar_hpte_getword0(slot);
	if ((dummy0 & ~0x7FUL) != (want_v & ~0x7FUL)) {
		DBG_LOW("not found !\n");
		spin_unlock(&beat_htab_lock);
		return -1;
	}

	lpar_rc = beat_write_htab_entry(0, slot, 0, newpp, 0, 7, &dummy0,
					&dummy1);
	spin_unlock(&beat_htab_lock);
	if (lpar_rc != 0 || dummy0 == 0) {
		DBG_LOW("not found !\n");
		return -1;
	}

	DBG_LOW("ok %lx %lx\n", dummy0, dummy1);

	BUG_ON(lpar_rc != 0);

	return 0;
}