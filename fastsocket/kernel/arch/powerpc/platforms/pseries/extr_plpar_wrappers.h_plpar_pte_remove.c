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
 int /*<<< orphan*/  H_REMOVE ; 
 int PLPAR_HCALL_BUFSIZE ; 
 long plpar_hcall (int /*<<< orphan*/ ,unsigned long*,unsigned long,unsigned long,unsigned long) ; 

__attribute__((used)) static inline long plpar_pte_remove(unsigned long flags, unsigned long ptex,
		unsigned long avpn, unsigned long *old_pteh_ret,
		unsigned long *old_ptel_ret)
{
	long rc;
	unsigned long retbuf[PLPAR_HCALL_BUFSIZE];

	rc = plpar_hcall(H_REMOVE, retbuf, flags, ptex, avpn);

	*old_pteh_ret = retbuf[0];
	*old_ptel_ret = retbuf[1];

	return rc;
}