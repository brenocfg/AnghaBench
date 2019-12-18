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
 int GP_DEVICE ; 
 int /*<<< orphan*/  OMAP24XX_VA_READPERM0 ; 
 int /*<<< orphan*/  OMAP24XX_VA_REQINFOPERM0 ; 
 int /*<<< orphan*/  OMAP24XX_VA_WRITEPERM0 ; 
 int OMAP2_DEVICETYPE_MASK ; 
 int /*<<< orphan*/  OMAP34XX_VA_ADDR_MATCH2 ; 
 int /*<<< orphan*/  OMAP34XX_VA_READPERM0 ; 
 int /*<<< orphan*/  OMAP34XX_VA_REQINFOPERM0 ; 
 int /*<<< orphan*/  OMAP34XX_VA_SMS_RG_ATT0 ; 
 int /*<<< orphan*/  OMAP34XX_VA_WRITEPERM0 ; 
 int /*<<< orphan*/  __raw_writel (int,int /*<<< orphan*/ ) ; 
 scalar_t__ cpu_is_omap242x () ; 
 scalar_t__ cpu_is_omap34xx () ; 
 scalar_t__ cpu_is_omap44xx () ; 
 int omap_rev () ; 

__attribute__((used)) static int is_sram_locked(void)
{
	int type = 0;

	if (cpu_is_omap44xx())
		/* Not yet supported */
		return 0;

	if (cpu_is_omap242x())
		type = omap_rev() & OMAP2_DEVICETYPE_MASK;

	if (type == GP_DEVICE) {
		/* RAMFW: R/W access to all initiators for all qualifier sets */
		if (cpu_is_omap242x()) {
			__raw_writel(0xFF, OMAP24XX_VA_REQINFOPERM0); /* all q-vects */
			__raw_writel(0xCFDE, OMAP24XX_VA_READPERM0);  /* all i-read */
			__raw_writel(0xCFDE, OMAP24XX_VA_WRITEPERM0); /* all i-write */
		}
		if (cpu_is_omap34xx()) {
			__raw_writel(0xFFFF, OMAP34XX_VA_REQINFOPERM0); /* all q-vects */
			__raw_writel(0xFFFF, OMAP34XX_VA_READPERM0);  /* all i-read */
			__raw_writel(0xFFFF, OMAP34XX_VA_WRITEPERM0); /* all i-write */
			__raw_writel(0x0, OMAP34XX_VA_ADDR_MATCH2);
			__raw_writel(0xFFFFFFFF, OMAP34XX_VA_SMS_RG_ATT0);
		}
		return 0;
	} else
		return 1; /* assume locked with no PPA or security driver */
}