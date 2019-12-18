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

/* Variables and functions */
 unsigned long HPTE_V_AVPN_VAL (unsigned long) ; 
 unsigned long HPTE_V_VALID ; 
 int /*<<< orphan*/  HvCallHpt_invalidateSetSwBitsGet (unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iSeries_hlock (unsigned long) ; 
 unsigned long iSeries_hpte_getword0 (unsigned long) ; 
 int /*<<< orphan*/  iSeries_hunlock (unsigned long) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 

__attribute__((used)) static void iSeries_hpte_invalidate(unsigned long slot, unsigned long va,
				    int psize, int ssize, int local)
{
	unsigned long hpte_v;
	unsigned long avpn = va >> 23;
	unsigned long flags;

	local_irq_save(flags);

	iSeries_hlock(slot);

	hpte_v = iSeries_hpte_getword0(slot);

	if ((HPTE_V_AVPN_VAL(hpte_v) == avpn) && (hpte_v & HPTE_V_VALID))
		HvCallHpt_invalidateSetSwBitsGet(slot, 0, 0);

	iSeries_hunlock(slot);

	local_irq_restore(flags);
}