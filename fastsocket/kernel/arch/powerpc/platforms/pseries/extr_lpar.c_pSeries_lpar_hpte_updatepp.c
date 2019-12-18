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
 unsigned long H_AVPN ; 
 unsigned long H_NOT_FOUND ; 
 unsigned long H_SUCCESS ; 
 unsigned long hpte_encode_avpn (unsigned long,int,int) ; 
 unsigned long plpar_pte_protect (unsigned long,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  pr_devel (char*,...) ; 

__attribute__((used)) static long pSeries_lpar_hpte_updatepp(unsigned long slot,
				       unsigned long newpp,
				       unsigned long va,
				       int psize, int ssize, int local)
{
	unsigned long lpar_rc;
	unsigned long flags = (newpp & 7) | H_AVPN;
	unsigned long want_v;

	want_v = hpte_encode_avpn(va, psize, ssize);

	pr_devel("    update: avpnv=%016lx, hash=%016lx, f=%lx, psize: %d ...",
		 want_v, slot, flags, psize);

	lpar_rc = plpar_pte_protect(flags, slot, want_v);

	if (lpar_rc == H_NOT_FOUND) {
		pr_devel("not found !\n");
		return -1;
	}

	pr_devel("ok\n");

	BUG_ON(lpar_rc != H_SUCCESS);

	return 0;
}