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
struct clk {TYPE_1__* parent; } ;
struct TYPE_2__ {unsigned long (* get_rate ) (TYPE_1__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  PLLDIV ; 
 int /*<<< orphan*/  PLLMUL ; 
 int PM_BFEXT (int /*<<< orphan*/ ,unsigned long) ; 
 unsigned long stub1 (TYPE_1__*) ; 

__attribute__((used)) static unsigned long pll_get_rate(struct clk *clk, unsigned long control)
{
	unsigned long div, mul, rate;

	div = PM_BFEXT(PLLDIV, control) + 1;
	mul = PM_BFEXT(PLLMUL, control) + 1;

	rate = clk->parent->get_rate(clk->parent);
	rate = (rate + div / 2) / div;
	rate *= mul;

	return rate;
}