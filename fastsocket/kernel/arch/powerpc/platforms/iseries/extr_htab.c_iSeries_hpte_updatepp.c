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
struct hash_pte {int v; } ;

/* Variables and functions */
 scalar_t__ HPTE_V_COMPARE (int,unsigned long) ; 
 int HPTE_V_VALID ; 
 int /*<<< orphan*/  HvCallHpt_get (struct hash_pte*,unsigned long) ; 
 int /*<<< orphan*/  HvCallHpt_setPp (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  MMU_PAGE_4K ; 
 int /*<<< orphan*/  MMU_SEGSIZE_256M ; 
 unsigned long hpte_encode_v (unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iSeries_hlock (unsigned long) ; 
 int /*<<< orphan*/  iSeries_hunlock (unsigned long) ; 

__attribute__((used)) static long iSeries_hpte_updatepp(unsigned long slot, unsigned long newpp,
			unsigned long va, int psize, int ssize, int local)
{
	struct hash_pte hpte;
	unsigned long want_v;

	iSeries_hlock(slot);

	HvCallHpt_get(&hpte, slot);
	want_v = hpte_encode_v(va, MMU_PAGE_4K, MMU_SEGSIZE_256M);

	if (HPTE_V_COMPARE(hpte.v, want_v) && (hpte.v & HPTE_V_VALID)) {
		/*
		 * Hypervisor expects bits as NPPP, which is
		 * different from how they are mapped in our PP.
		 */
		HvCallHpt_setPp(slot, (newpp & 0x3) | ((newpp & 0x4) << 1));
		iSeries_hunlock(slot);
		return 0;
	}
	iSeries_hunlock(slot);

	return -1;
}