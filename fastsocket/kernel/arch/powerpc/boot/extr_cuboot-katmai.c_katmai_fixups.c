#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  bi_enetaddr; } ;

/* Variables and functions */
 TYPE_1__ bd ; 
 int /*<<< orphan*/  dt_fixup_mac_address (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ibm440spe_fixup_clocks (unsigned long,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ibm440spe_fixup_memsize () ; 
 int /*<<< orphan*/  ibm4xx_fixup_ebc_ranges (char*) ; 

__attribute__((used)) static void katmai_fixups(void)
{
	unsigned long sysclk = 33333000;

	/* 440SP Clock logic is all but identical to 440GX
	 * so we just use that code for now at least
	 */
	ibm440spe_fixup_clocks(sysclk, 6 * 1843200, 0);

	ibm440spe_fixup_memsize();

	dt_fixup_mac_address(0, bd.bi_enetaddr);

	ibm4xx_fixup_ebc_ranges("/plb/opb/ebc");
}