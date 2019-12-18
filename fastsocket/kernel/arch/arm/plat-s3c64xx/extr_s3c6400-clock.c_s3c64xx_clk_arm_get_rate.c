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
struct clk {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  S3C_CLK_DIV0 ; 
 int __raw_readl (int /*<<< orphan*/ ) ; 
 int armclk_mask ; 
 unsigned long clk_get_rate (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned long s3c64xx_clk_arm_get_rate(struct clk *clk)
{
	unsigned long rate = clk_get_rate(clk->parent);
	u32 clkdiv;

	/* divisor mask starts at bit0, so no need to shift */
	clkdiv = __raw_readl(S3C_CLK_DIV0) & armclk_mask;

	return rate / (clkdiv + 1);
}