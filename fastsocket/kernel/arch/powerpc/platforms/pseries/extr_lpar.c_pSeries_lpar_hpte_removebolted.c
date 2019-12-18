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
 unsigned long get_kernel_vsid (unsigned long,int) ; 
 unsigned long hpt_va (unsigned long,unsigned long,int) ; 
 unsigned long pSeries_lpar_hpte_find (unsigned long,int,int) ; 
 int /*<<< orphan*/  pSeries_lpar_hpte_invalidate (unsigned long,unsigned long,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pSeries_lpar_hpte_removebolted(unsigned long ea,
					   int psize, int ssize)
{
	unsigned long slot, vsid, va;

	vsid = get_kernel_vsid(ea, ssize);
	va = hpt_va(ea, vsid, ssize);

	slot = pSeries_lpar_hpte_find(va, psize, ssize);
	BUG_ON(slot == -1);

	pSeries_lpar_hpte_invalidate(slot, va, psize, ssize, 0);
}