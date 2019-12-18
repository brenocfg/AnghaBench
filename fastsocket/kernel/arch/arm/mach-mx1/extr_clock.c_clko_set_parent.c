#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct clk {int /*<<< orphan*/ * round_rate; int /*<<< orphan*/ * set_rate; } ;
struct TYPE_4__ {scalar_t__ round_rate; scalar_t__ set_rate; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (TYPE_1__**) ; 
 int /*<<< orphan*/  CCM_CSCR ; 
 unsigned int CCM_CSCR_CLKO_MASK ; 
 int CCM_CSCR_CLKO_OFFSET ; 
 unsigned int __raw_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writel (unsigned int,int /*<<< orphan*/ ) ; 
 int _clk_can_use_parent (TYPE_1__**,int /*<<< orphan*/ ,struct clk*) ; 
 int /*<<< orphan*/ * _clk_parent_round_rate ; 
 int /*<<< orphan*/ * _clk_parent_set_rate ; 
 TYPE_1__** clko_clocks ; 

__attribute__((used)) static int clko_set_parent(struct clk *clk, struct clk *parent)
{
	int i;
	unsigned int reg;

	i = _clk_can_use_parent(clko_clocks, ARRAY_SIZE(clko_clocks), parent);
	if (i < 0)
		return i;

	reg = __raw_readl(CCM_CSCR) & ~CCM_CSCR_CLKO_MASK;
	reg |= i << CCM_CSCR_CLKO_OFFSET;
	__raw_writel(reg, CCM_CSCR);

	if (clko_clocks[i]->set_rate && clko_clocks[i]->round_rate) {
		clk->set_rate = _clk_parent_set_rate;
		clk->round_rate = _clk_parent_round_rate;
	} else {
		clk->set_rate = NULL;
		clk->round_rate = NULL;
	}

	return 0;
}