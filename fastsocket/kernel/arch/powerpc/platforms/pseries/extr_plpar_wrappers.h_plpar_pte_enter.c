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
 int /*<<< orphan*/  H_ENTER ; 
 int PLPAR_HCALL_BUFSIZE ; 
 long plpar_hcall (int /*<<< orphan*/ ,unsigned long*,unsigned long,unsigned long,unsigned long,unsigned long) ; 

__attribute__((used)) static inline long plpar_pte_enter(unsigned long flags,
		unsigned long hpte_group, unsigned long hpte_v,
		unsigned long hpte_r, unsigned long *slot)
{
	long rc;
	unsigned long retbuf[PLPAR_HCALL_BUFSIZE];

	rc = plpar_hcall(H_ENTER, retbuf, flags, hpte_group, hpte_v, hpte_r);

	*slot = retbuf[0];

	return rc;
}