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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  H_VTERM_PARTNER_INFO ; 
 int hvcs_convert (long) ; 
 long plpar_hcall_norets (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virt_to_phys (unsigned long*) ; 

__attribute__((used)) static int hvcs_next_partner(uint32_t unit_address,
		unsigned long last_p_partition_ID,
		unsigned long last_p_unit_address, unsigned long *pi_buff)

{
	long retval;
	retval = plpar_hcall_norets(H_VTERM_PARTNER_INFO, unit_address,
			last_p_partition_ID,
				last_p_unit_address, virt_to_phys(pi_buff));
	return hvcs_convert(retval);
}