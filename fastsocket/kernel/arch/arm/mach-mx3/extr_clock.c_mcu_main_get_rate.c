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
struct clk {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MXC_CCM_PMCR0 ; 
 int MXC_CCM_PMCR0_DFSUP1 ; 
 int MXC_CCM_PMCR0_DFSUP1_SPLL ; 
 int __raw_readl (int /*<<< orphan*/ ) ; 
 unsigned long clk_get_rate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mcu_pll_clk ; 
 int /*<<< orphan*/  serial_pll_clk ; 

__attribute__((used)) static unsigned long mcu_main_get_rate(struct clk *clk)
{
	u32 pmcr0 = __raw_readl(MXC_CCM_PMCR0);

	if ((pmcr0 & MXC_CCM_PMCR0_DFSUP1) == MXC_CCM_PMCR0_DFSUP1_SPLL)
		return clk_get_rate(&serial_pll_clk);
	else
		return clk_get_rate(&mcu_pll_clk);
}