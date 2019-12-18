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
struct clk {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCM_PCDR ; 
 unsigned int CCM_PCDR_PCLK2_MASK ; 
 unsigned int CCM_PCDR_PCLK2_OFFSET ; 
 int EINVAL ; 
 unsigned int __raw_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writel (unsigned int,int /*<<< orphan*/ ) ; 
 unsigned long clk_get_rate (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int perclk2_set_rate(struct clk *clk, unsigned long rate)
{
	unsigned int div;
	unsigned int reg;
	unsigned long parent_rate;

	parent_rate = clk_get_rate(clk->parent);

	div = parent_rate / rate;

	if (div > 16 || div < 1 || ((parent_rate / div) != rate))
		return -EINVAL;

	div--;

	reg = __raw_readl(CCM_PCDR);
	reg &= ~CCM_PCDR_PCLK2_MASK;
	reg |= div << CCM_PCDR_PCLK2_OFFSET;
	__raw_writel(reg, CCM_PCDR);

	return 0;
}