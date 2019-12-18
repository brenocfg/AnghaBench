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
struct clk {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  S5PC100_CLKSRC1_CLK48M_MASK ; 
 int /*<<< orphan*/  S5PC1XX_CLK_SRC1 ; 
 int /*<<< orphan*/  __raw_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 

__attribute__((used)) static int clk_48m_ctrl(struct clk *clk, int enable)
{
	unsigned long flags;
	u32 val;

	/* can't rely on clock lock, this register has other usages */
	local_irq_save(flags);

	val = __raw_readl(S5PC1XX_CLK_SRC1);
	if (enable)
		val |= S5PC100_CLKSRC1_CLK48M_MASK;
	else
		val &= ~S5PC100_CLKSRC1_CLK48M_MASK;

	__raw_writel(val, S5PC1XX_CLK_SRC1);
	local_irq_restore(flags);

	return 0;
}