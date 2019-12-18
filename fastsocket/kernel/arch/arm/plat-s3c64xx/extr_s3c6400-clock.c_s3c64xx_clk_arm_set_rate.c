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
 int EINVAL ; 
 int /*<<< orphan*/  S3C_CLK_DIV0 ; 
 int __raw_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writel (int,int /*<<< orphan*/ ) ; 
 int armclk_mask ; 
 unsigned long clk_get_rate (int /*<<< orphan*/ ) ; 
 unsigned long clk_round_rate (struct clk*,unsigned long) ; 

__attribute__((used)) static int s3c64xx_clk_arm_set_rate(struct clk *clk, unsigned long rate)
{
	unsigned long parent = clk_get_rate(clk->parent);
	u32 div;
	u32 val;

	if (rate < parent / (armclk_mask + 1))
		return -EINVAL;

	rate = clk_round_rate(clk, rate);
	div = clk_get_rate(clk->parent) / rate;

	val = __raw_readl(S3C_CLK_DIV0);
	val &= ~armclk_mask;
	val |= (div - 1);
	__raw_writel(val, S3C_CLK_DIV0);

	return 0;

}