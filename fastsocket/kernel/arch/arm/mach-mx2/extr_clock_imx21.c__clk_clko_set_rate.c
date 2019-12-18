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
struct clk {int /*<<< orphan*/ * parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCM_PCDR0 ; 
 int CCM_PCDR0_48MDIV_MASK ; 
 int CCM_PCDR0_48MDIV_OFFSET ; 
 int EINVAL ; 
 int __raw_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writel (int,int /*<<< orphan*/ ) ; 
 unsigned long clk_get_rate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * usb_clk ; 

__attribute__((used)) static int _clk_clko_set_rate(struct clk *clk, unsigned long rate)
{
	u32 reg;
	u32 div;
	unsigned long parent_rate;

	parent_rate = clk_get_rate(clk->parent);

	div = parent_rate / rate;

	if (div > 8 || div < 1 || ((parent_rate / div) != rate))
		return -EINVAL;
	div--;

	reg = __raw_readl(CCM_PCDR0);

	if (clk->parent == &usb_clk[0]) {
		reg &= ~CCM_PCDR0_48MDIV_MASK;
		reg |= div << CCM_PCDR0_48MDIV_OFFSET;
	}
	__raw_writel(reg, CCM_PCDR0);

	return 0;
}