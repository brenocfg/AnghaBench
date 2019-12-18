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
 int /*<<< orphan*/  CCM_PCDR1 ; 
 int __raw_readl (int /*<<< orphan*/ ) ; 
 unsigned long clk_get_rate (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned long get_rate_per(struct clk *clk)
{
	unsigned long perclk_pdf, parent_rate;

	parent_rate = clk_get_rate(clk->parent);

	if (clk->id < 0 || clk->id > 3)
		return 0;

	perclk_pdf = (__raw_readl(CCM_PCDR1) >> (clk->id << 3)) & 0x3f;

	return parent_rate / (perclk_pdf + 1);
}