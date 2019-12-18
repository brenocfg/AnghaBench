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
 int OMAP_SYSCLKDIV_MASK ; 
 int OMAP_SYSCLKDIV_SHIFT ; 
 int __raw_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prcm_clksrc_ctrl ; 

__attribute__((used)) static u32 omap2_get_sysclkdiv(void)
{
	u32 div;

	div = __raw_readl(prcm_clksrc_ctrl);
	div &= OMAP_SYSCLKDIV_MASK;
	div >>= OMAP_SYSCLKDIV_SHIFT;

	return div;
}