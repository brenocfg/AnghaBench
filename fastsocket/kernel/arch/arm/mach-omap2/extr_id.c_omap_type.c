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
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  OMAP24XX_CONTROL_STATUS ; 
 int OMAP2_DEVICETYPE_MASK ; 
 int /*<<< orphan*/  OMAP343X_CONTROL_STATUS ; 
 scalar_t__ cpu_is_omap24xx () ; 
 scalar_t__ cpu_is_omap34xx () ; 
 int omap_ctrl_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

int omap_type(void)
{
	u32 val = 0;

	if (cpu_is_omap24xx())
		val = omap_ctrl_readl(OMAP24XX_CONTROL_STATUS);
	else if (cpu_is_omap34xx())
		val = omap_ctrl_readl(OMAP343X_CONTROL_STATUS);
	else {
		pr_err("Cannot detect omap type!\n");
		goto out;
	}

	val &= OMAP2_DEVICETYPE_MASK;
	val >>= 8;

out:
	return val;
}