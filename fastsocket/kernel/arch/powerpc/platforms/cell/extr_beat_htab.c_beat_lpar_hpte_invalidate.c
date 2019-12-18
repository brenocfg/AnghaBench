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
 int /*<<< orphan*/  HPTE_V_VALID ; 
 int /*<<< orphan*/  MMU_SEGSIZE_256M ; 
 int /*<<< orphan*/  beat_htab_lock ; 
 int beat_lpar_hpte_getword0 (unsigned long) ; 
 unsigned long beat_write_htab_entry (int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*) ; 
 unsigned long hpte_encode_v (unsigned long,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void beat_lpar_hpte_invalidate(unsigned long slot, unsigned long va,
					 int psize, int ssize, int local)
{
	unsigned long want_v;
	unsigned long lpar_rc;
	u64 dummy1, dummy2;
	unsigned long flags;

	DBG_LOW("    inval : slot=%lx, va=%016lx, psize: %d, local: %d\n",
		slot, va, psize, local);
	want_v = hpte_encode_v(va, psize, MMU_SEGSIZE_256M);

	spin_lock_irqsave(&beat_htab_lock, flags);
	dummy1 = beat_lpar_hpte_getword0(slot);

	if ((dummy1 & ~0x7FUL) != (want_v & ~0x7FUL)) {
		DBG_LOW("not found !\n");
		spin_unlock_irqrestore(&beat_htab_lock, flags);
		return;
	}

	lpar_rc = beat_write_htab_entry(0, slot, 0, 0, HPTE_V_VALID, 0,
		&dummy1, &dummy2);
	spin_unlock_irqrestore(&beat_htab_lock, flags);

	BUG_ON(lpar_rc != 0);
}