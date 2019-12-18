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
struct clk {int rate; int /*<<< orphan*/  scale_reg; } ;

/* Variables and functions */
 int __raw_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hclk_set_rate(struct clk *clk, u32 rate)
{
	u32 tmp;
	tmp = __raw_readl(clk->scale_reg);
	tmp = tmp & ~0x3;
	switch (rate) {
	case 1:
		break;
	case 2:
		tmp |= 1;
		break;
	case 4:
		tmp |= 2;
		break;
	}

	__raw_writel(tmp, clk->scale_reg);
	clk->rate = rate;
	return 0;
}