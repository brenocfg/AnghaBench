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
struct clk {int rate; TYPE_1__* parent; } ;
struct TYPE_2__ {int rate; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPG2_FRQCR3 ; 
 int EINVAL ; 
 unsigned long ctrl_inl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctrl_outl (unsigned long,int /*<<< orphan*/ ) ; 
 int* frqcr3_divisors ; 
 unsigned int frqcr3_lookup (struct clk*,unsigned long) ; 
 scalar_t__ shoc_clk_verify_rate (struct clk*,unsigned long) ; 

__attribute__((used)) static int shoc_clk_set_rate(struct clk *clk, unsigned long rate, int algo_id)
{
	unsigned long frqcr3;
	unsigned int tmp;

	/* Make sure we have something sensible to switch to */
	if (shoc_clk_verify_rate(clk, rate) != 0)
		return -EINVAL;

	tmp = frqcr3_lookup(clk, rate);

	frqcr3 = ctrl_inl(CPG2_FRQCR3);
	frqcr3 &= ~(0x0007 << 6);
	frqcr3 |= tmp << 6;
	ctrl_outl(frqcr3, CPG2_FRQCR3);

	clk->rate = clk->parent->rate / frqcr3_divisors[tmp];

	return 0;
}