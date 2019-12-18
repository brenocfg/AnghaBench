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
typedef  int /*<<< orphan*/  uint32_t ;
struct clk {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCM_SPCTL0 ; 
 scalar_t__ CHIP_REV_2_0 ; 
 int /*<<< orphan*/  __raw_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned long clk_get_rate (int /*<<< orphan*/ ) ; 
 scalar_t__ mx27_revision () ; 
 unsigned long mxc_decode_pll (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static unsigned long get_rate_spll(struct clk *clk)
{
	uint32_t reg;
	unsigned long rate;

	rate = clk_get_rate(clk->parent);

	reg = __raw_readl(CCM_SPCTL0);

	/* On TO2 we have to write the value back. Otherwise we
	 * read 0 from this register the next time.
	 */
	if (mx27_revision() >= CHIP_REV_2_0)
		__raw_writel(reg, CCM_SPCTL0);

	return mxc_decode_pll(reg, rate);
}