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
typedef  int u16 ;
struct clk {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ U300_SYSCON_MMCR ; 
 int U300_SYSCON_MMCR_MMC_FB_CLK_SEL_ENABLE ; 
 int U300_SYSCON_MMCR_MSPRO_FREQSEL_ENABLE ; 
 scalar_t__ U300_SYSCON_MMF0R ; 
 scalar_t__ U300_SYSCON_VBASE ; 
 int readw (scalar_t__) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  writew (int,scalar_t__) ; 

int __clk_get(struct clk *clk)
{
	u16 val;

	/* The MMC and MSPRO clocks need some special set-up */
	if (!strcmp(clk->name, "MCLK")) {
		/* Set default MMC clock divisor to 18.9 MHz */
		writew(0x0054U, U300_SYSCON_VBASE + U300_SYSCON_MMF0R);
		val = readw(U300_SYSCON_VBASE + U300_SYSCON_MMCR);
		/* Disable the MMC feedback clock */
		val &= ~U300_SYSCON_MMCR_MMC_FB_CLK_SEL_ENABLE;
		/* Disable MSPRO frequency */
		val &= ~U300_SYSCON_MMCR_MSPRO_FREQSEL_ENABLE;
		writew(val, U300_SYSCON_VBASE + U300_SYSCON_MMCR);
	}
	if (!strcmp(clk->name, "MSPRO")) {
		val = readw(U300_SYSCON_VBASE + U300_SYSCON_MMCR);
		/* Disable the MMC feedback clock */
		val &= ~U300_SYSCON_MMCR_MMC_FB_CLK_SEL_ENABLE;
		/* Enable MSPRO frequency */
		val |= U300_SYSCON_MMCR_MSPRO_FREQSEL_ENABLE;
		writew(val, U300_SYSCON_VBASE + U300_SYSCON_MMCR);
	}
	return 1;
}