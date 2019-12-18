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
typedef  unsigned long u32 ;
struct clk {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MXC_CCM_PDR1 ; 
 unsigned long MXC_CCM_PDR1_FIRI_PODF_MASK ; 
 unsigned long MXC_CCM_PDR1_FIRI_PODF_OFFSET ; 
 unsigned long MXC_CCM_PDR1_FIRI_PRE_PODF_MASK ; 
 unsigned long MXC_CCM_PDR1_FIRI_PRE_PODF_OFFSET ; 
 int /*<<< orphan*/  __calc_pre_post_dividers (unsigned long,unsigned long*,unsigned long*) ; 
 unsigned long __raw_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writel (unsigned long,int /*<<< orphan*/ ) ; 
 unsigned long clk_get_rate (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int firi_set_rate(struct clk *clk, unsigned long rate)
{
	u32 reg, div, pre, post, parent = clk_get_rate(clk->parent);

	div = parent / rate;

	if ((parent / div) != rate)
		return -EINVAL;

	__calc_pre_post_dividers(div, &pre, &post);

	/* Set FIRI clock divider */
	reg = __raw_readl(MXC_CCM_PDR1) &
	    ~(MXC_CCM_PDR1_FIRI_PODF_MASK | MXC_CCM_PDR1_FIRI_PRE_PODF_MASK);
	reg |= (pre - 1) << MXC_CCM_PDR1_FIRI_PRE_PODF_OFFSET;
	reg |= (post - 1) << MXC_CCM_PDR1_FIRI_PODF_OFFSET;
	__raw_writel(reg, MXC_CCM_PDR1);

	return 0;
}