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
struct clk {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCM_PCDR ; 
 int CCM_PCDR_PCLK2_MASK ; 
 int CCM_PCDR_PCLK2_OFFSET ; 
 int __raw_readl (int /*<<< orphan*/ ) ; 
 int clk_get_rate (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned long perclk2_get_rate(struct clk *clk)
{
	return clk_get_rate(clk->parent) / (((__raw_readl(CCM_PCDR) &
			CCM_PCDR_PCLK2_MASK) >> CCM_PCDR_PCLK2_OFFSET) + 1);
}