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
struct clk {int id; int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int CCM_PCDR1_PERDIV1_MASK ; 
 int PCDR1 () ; 
 unsigned long clk_get_rate (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned long _clk_perclkx_recalc(struct clk *clk)
{
	unsigned long perclk_pdf;
	unsigned long parent_rate;

	parent_rate = clk_get_rate(clk->parent);

	if (clk->id < 0 || clk->id > 3)
		return 0;

	perclk_pdf = (PCDR1() >> (clk->id << 3)) & CCM_PCDR1_PERDIV1_MASK;

	return parent_rate / (perclk_pdf + 1);
}