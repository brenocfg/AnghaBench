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
 unsigned long H_SUCCESS ; 
 unsigned long get_kernel_vsid (unsigned long,int) ; 
 unsigned long hpt_va (unsigned long,unsigned long,int) ; 
 unsigned long pSeries_lpar_hpte_find (unsigned long,int,int) ; 
 unsigned long plpar_pte_protect (unsigned long,unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pSeries_lpar_hpte_updateboltedpp(unsigned long newpp,
					     unsigned long ea,
					     int psize, int ssize)
{
	unsigned long lpar_rc, slot, vsid, va, flags;

	vsid = get_kernel_vsid(ea, ssize);
	va = hpt_va(ea, vsid, ssize);

	slot = pSeries_lpar_hpte_find(va, psize, ssize);
	BUG_ON(slot == -1);

	flags = newpp & 7;
	lpar_rc = plpar_pte_protect(flags, slot, 0);

	BUG_ON(lpar_rc != H_SUCCESS);
}