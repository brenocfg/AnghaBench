#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct clk {int rate; int /*<<< orphan*/  scale_reg; TYPE_1__* parent; } ;
struct TYPE_2__ {int rate; } ;

/* Variables and functions */
 int __raw_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int per_clk_set_rate(struct clk *clk, u32 rate)
{
	u32 tmp;

	tmp = __raw_readl(clk->scale_reg);
	tmp &= ~(0x1f << 2);
	tmp |= ((clk->parent->rate / clk->rate) - 1) << 2;
	__raw_writel(tmp, clk->scale_reg);
	clk->rate = rate;
	return 0;
}