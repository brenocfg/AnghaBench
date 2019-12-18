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
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 unsigned long HPTE_V_BOLTED ; 
 unsigned long HPTE_V_SECONDARY ; 
 unsigned long HPTE_V_VALID ; 
 unsigned long HW_PAGE_SHIFT ; 
 int /*<<< orphan*/  HvCallHpt_addValidate (long,int,struct hash_pte*) ; 
 long HvCallHpt_findValid (struct hash_pte*,unsigned long) ; 
 int /*<<< orphan*/  HvCallHpt_setPp (long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HvCallHpt_setSwBits (long,int,int /*<<< orphan*/ ) ; 
 int MMU_PAGE_4K ; 
 int /*<<< orphan*/  MMU_SEGSIZE_256M ; 
 int /*<<< orphan*/  PP_RWXX ; 
 unsigned long hpte_encode_r (int /*<<< orphan*/ ,int) ; 
 unsigned long hpte_encode_v (unsigned long,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iSeries_hlock (unsigned long) ; 
 int /*<<< orphan*/  iSeries_hunlock (unsigned long) ; 
 int /*<<< orphan*/  phys_to_abs (unsigned long) ; 
 scalar_t__ unlikely (unsigned long) ; 

__attribute__((used)) static long iSeries_hpte_insert(unsigned long hpte_group, unsigned long va,
			 unsigned long pa, unsigned long rflags,
			 unsigned long vflags, int psize, int ssize)
{
	long slot;
	struct hash_pte lhpte;
	int secondary = 0;

	BUG_ON(psize != MMU_PAGE_4K);

	/*
	 * The hypervisor tries both primary and secondary.
	 * If we are being called to insert in the secondary,
	 * it means we have already tried both primary and secondary,
	 * so we return failure immediately.
	 */
	if (vflags & HPTE_V_SECONDARY)
		return -1;

	iSeries_hlock(hpte_group);

	slot = HvCallHpt_findValid(&lhpte, va >> HW_PAGE_SHIFT);
	if (unlikely(lhpte.v & HPTE_V_VALID)) {
		if (vflags & HPTE_V_BOLTED) {
			HvCallHpt_setSwBits(slot, 0x10, 0);
			HvCallHpt_setPp(slot, PP_RWXX);
			iSeries_hunlock(hpte_group);
			if (slot < 0)
				return 0x8 | (slot & 7);
			else
				return slot & 7;
		}
		BUG();
	}

	if (slot == -1)	{ /* No available entry found in either group */
		iSeries_hunlock(hpte_group);
		return -1;
	}

	if (slot < 0) {		/* MSB set means secondary group */
		vflags |= HPTE_V_SECONDARY;
		secondary = 1;
		slot &= 0x7fffffffffffffff;
	}


	lhpte.v = hpte_encode_v(va, MMU_PAGE_4K, MMU_SEGSIZE_256M) |
		vflags | HPTE_V_VALID;
	lhpte.r = hpte_encode_r(phys_to_abs(pa), MMU_PAGE_4K) | rflags;

	/* Now fill in the actual HPTE */
	HvCallHpt_addValidate(slot, secondary, &lhpte);

	iSeries_hunlock(hpte_group);

	return (secondary << 3) | (slot & 7);
}