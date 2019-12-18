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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  MXC_CRMAP_AMCR ; 
 int /*<<< orphan*/  MXC_CRMAP_AMCR_SW_AP ; 
 int /*<<< orphan*/  __raw_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdelay (int) ; 

void mxc91231_arch_reset(char mode, const char *cmd)
{
	u32 amcr;

	/* Reset the AP using CRM */
	amcr = __raw_readl(MXC_CRMAP_AMCR);
	amcr &= ~MXC_CRMAP_AMCR_SW_AP;
	__raw_writel(amcr, MXC_CRMAP_AMCR);

	mdelay(10);
	cpu_reset(0);
}