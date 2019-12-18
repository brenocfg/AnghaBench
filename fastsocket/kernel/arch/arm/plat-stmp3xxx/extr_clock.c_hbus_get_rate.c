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
struct clk {long rate; int /*<<< orphan*/  scale_reg; TYPE_1__* parent; } ;
struct TYPE_2__ {long rate; } ;

/* Variables and functions */
 int __raw_readl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static long hbus_get_rate(struct clk *clk)
{
	long rate = clk->parent->rate;

	if (__raw_readl(clk->scale_reg) & 0x20) {
		rate *= __raw_readl(clk->scale_reg) & 0x1f;
		rate /= 32;
	} else
		rate /= __raw_readl(clk->scale_reg) & 0x1f;
	clk->rate = rate;

	return rate;
}