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
 int /*<<< orphan*/  H_SEND_LOGICAL_LAN ; 
 int PLPAR_HCALL9_BUFSIZE ; 
 long plpar_hcall9 (int /*<<< orphan*/ ,unsigned long*,unsigned long,unsigned long,unsigned long,unsigned long,unsigned long,unsigned long,unsigned long,unsigned long) ; 

__attribute__((used)) static inline long h_send_logical_lan(unsigned long unit_address,
		unsigned long desc1, unsigned long desc2, unsigned long desc3,
		unsigned long desc4, unsigned long desc5, unsigned long desc6,
		unsigned long corellator_in, unsigned long *corellator_out)
{
	long rc;
	unsigned long retbuf[PLPAR_HCALL9_BUFSIZE];

	rc = plpar_hcall9(H_SEND_LOGICAL_LAN, retbuf, unit_address, desc1,
			desc2, desc3, desc4, desc5, desc6, corellator_in);

	*corellator_out = retbuf[0];

	return rc;
}