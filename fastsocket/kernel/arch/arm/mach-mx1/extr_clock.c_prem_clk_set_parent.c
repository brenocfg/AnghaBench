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
struct clk {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CCM_CSCR ; 
 unsigned int CCM_CSCR_SYSTEM_SEL ; 
 unsigned int __raw_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writel (unsigned int,int /*<<< orphan*/ ) ; 
 int _clk_can_use_parent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct clk*) ; 
 int /*<<< orphan*/  prem_clk_clocks ; 

__attribute__((used)) static int prem_clk_set_parent(struct clk *clk, struct clk *parent)
{
	int i;
	unsigned int reg = __raw_readl(CCM_CSCR);

	i = _clk_can_use_parent(prem_clk_clocks, ARRAY_SIZE(prem_clk_clocks),
				parent);

	switch (i) {
	case 0:
		reg &= ~CCM_CSCR_SYSTEM_SEL;
		break;
	case 1:
		reg |= CCM_CSCR_SYSTEM_SEL;
		break;
	default:
		return i;
	}

	__raw_writel(reg, CCM_CSCR);

	return 0;
}