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
 int /*<<< orphan*/  dt_fixup_mac_address_by_alias (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ebony_flashsel_fixup () ; 
 int /*<<< orphan*/  ebony_mac0 ; 
 int /*<<< orphan*/  ebony_mac1 ; 
 int /*<<< orphan*/  ibm440gp_fixup_clocks (unsigned long,int) ; 
 int /*<<< orphan*/  ibm4xx_fixup_ebc_ranges (char*) ; 
 int /*<<< orphan*/  ibm4xx_sdram_fixup_memsize () ; 

__attribute__((used)) static void ebony_fixups(void)
{
	// FIXME: sysclk should be derived by reading the FPGA registers
	unsigned long sysclk = 33000000;

	ibm440gp_fixup_clocks(sysclk, 6 * 1843200);
	ibm4xx_sdram_fixup_memsize();
	dt_fixup_mac_address_by_alias("ethernet0", ebony_mac0);
	dt_fixup_mac_address_by_alias("ethernet1", ebony_mac1);
	ibm4xx_fixup_ebc_ranges("/plb/opb/ebc");
	ebony_flashsel_fixup();
}