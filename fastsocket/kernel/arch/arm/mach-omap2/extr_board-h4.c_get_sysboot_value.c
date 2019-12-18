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
 int OMAP2_SYSBOOT_0_MASK ; 
 int OMAP2_SYSBOOT_1_MASK ; 
 int OMAP2_SYSBOOT_2_MASK ; 
 int OMAP2_SYSBOOT_3_MASK ; 
 int OMAP2_SYSBOOT_4_MASK ; 
 int OMAP2_SYSBOOT_5_MASK ; 
 int omap_ctrl_readl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 get_sysboot_value(void)
{
	return (omap_ctrl_readl(OMAP24XX_CONTROL_STATUS) &
		(OMAP2_SYSBOOT_5_MASK | OMAP2_SYSBOOT_4_MASK |
		 OMAP2_SYSBOOT_3_MASK | OMAP2_SYSBOOT_2_MASK |
		 OMAP2_SYSBOOT_1_MASK | OMAP2_SYSBOOT_0_MASK));
}