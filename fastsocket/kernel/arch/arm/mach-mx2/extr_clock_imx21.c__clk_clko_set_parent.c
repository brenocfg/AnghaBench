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
struct clk {struct clk* parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCM_CCSR ; 
 int CCM_CCSR_CLKOSEL_MASK ; 
 int CCM_CCSR_CLKOSEL_OFFSET ; 
 int EINVAL ; 
 int __raw_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writel (int,int /*<<< orphan*/ ) ; 
 struct clk ckih_clk ; 
 struct clk ckil_clk ; 
 struct clk clko_clk ; 
 struct clk fclk_clk ; 
 struct clk fpm_clk ; 
 struct clk hclk_clk ; 
 struct clk ipg_clk ; 
 struct clk mpll_clk ; 
 struct clk nfc_clk ; 
 struct clk* per_clk ; 
 struct clk spll_clk ; 
 struct clk* ssi_clk ; 
 struct clk* usb_clk ; 

__attribute__((used)) static int _clk_clko_set_parent(struct clk *clk, struct clk *parent)
{
	u32 reg;

	reg = __raw_readl(CCM_CCSR) & ~CCM_CCSR_CLKOSEL_MASK;

	if (parent == &ckil_clk)
		reg |= 0 << CCM_CCSR_CLKOSEL_OFFSET;
	else if (parent == &fpm_clk)
		reg |= 1 << CCM_CCSR_CLKOSEL_OFFSET;
	else if (parent == &ckih_clk)
		reg |= 2 << CCM_CCSR_CLKOSEL_OFFSET;
	else if (parent == mpll_clk.parent)
		reg |= 3 << CCM_CCSR_CLKOSEL_OFFSET;
	else if (parent == spll_clk.parent)
		reg |= 4 << CCM_CCSR_CLKOSEL_OFFSET;
	else if (parent == &mpll_clk)
		reg |= 5 << CCM_CCSR_CLKOSEL_OFFSET;
	else if (parent == &spll_clk)
		reg |= 6 << CCM_CCSR_CLKOSEL_OFFSET;
	else if (parent == &fclk_clk)
		reg |= 7 << CCM_CCSR_CLKOSEL_OFFSET;
	else if (parent == &hclk_clk)
		reg |= 8 << CCM_CCSR_CLKOSEL_OFFSET;
	else if (parent == &ipg_clk)
		reg |= 9 << CCM_CCSR_CLKOSEL_OFFSET;
	else if (parent == &per_clk[0])
		reg |= 0xA << CCM_CCSR_CLKOSEL_OFFSET;
	else if (parent == &per_clk[1])
		reg |= 0xB << CCM_CCSR_CLKOSEL_OFFSET;
	else if (parent == &per_clk[2])
		reg |= 0xC << CCM_CCSR_CLKOSEL_OFFSET;
	else if (parent == &per_clk[3])
		reg |= 0xD << CCM_CCSR_CLKOSEL_OFFSET;
	else if (parent == &ssi_clk[0])
		reg |= 0xE << CCM_CCSR_CLKOSEL_OFFSET;
	else if (parent == &ssi_clk[1])
		reg |= 0xF << CCM_CCSR_CLKOSEL_OFFSET;
	else if (parent == &nfc_clk)
		reg |= 0x10 << CCM_CCSR_CLKOSEL_OFFSET;
	else if (parent == &usb_clk[0])
		reg |= 0x14 << CCM_CCSR_CLKOSEL_OFFSET;
	else if (parent == &clko_clk)
		reg |= 0x15 << CCM_CCSR_CLKOSEL_OFFSET;
	else
		return -EINVAL;

	__raw_writel(reg, CCM_CCSR);

	return 0;
}