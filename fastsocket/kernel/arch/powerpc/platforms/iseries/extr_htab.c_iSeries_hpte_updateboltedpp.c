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
 int /*<<< orphan*/  BUG_ON (int) ; 
 unsigned long HW_PAGE_SHIFT ; 
 int /*<<< orphan*/  HvCallHpt_setPp (long,unsigned long) ; 
 int MMU_PAGE_4K ; 
 int /*<<< orphan*/  MMU_SEGSIZE_256M ; 
 unsigned long get_kernel_vsid (unsigned long,int /*<<< orphan*/ ) ; 
 long iSeries_hpte_find (unsigned long) ; 
 int /*<<< orphan*/  panic (char*) ; 

__attribute__((used)) static void iSeries_hpte_updateboltedpp(unsigned long newpp, unsigned long ea,
					int psize, int ssize)
{
	unsigned long vsid,va,vpn;
	long slot;

	BUG_ON(psize != MMU_PAGE_4K);

	vsid = get_kernel_vsid(ea, MMU_SEGSIZE_256M);
	va = (vsid << 28) | (ea & 0x0fffffff);
	vpn = va >> HW_PAGE_SHIFT;
	slot = iSeries_hpte_find(vpn);
	if (slot == -1)
		panic("updateboltedpp: Could not find page to bolt\n");
	HvCallHpt_setPp(slot, newpp);
}