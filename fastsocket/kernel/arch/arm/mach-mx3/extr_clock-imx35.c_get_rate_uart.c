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
struct clk {int dummy; } ;

/* Variables and functions */
 scalar_t__ CCM_BASE ; 
 scalar_t__ CCM_PDR3 ; 
 scalar_t__ CCM_PDR4 ; 
 unsigned long __raw_readl (scalar_t__) ; 
 unsigned long get_3_3_div (unsigned long) ; 
 unsigned long get_rate_arm () ; 
 unsigned long get_rate_ppll () ; 

__attribute__((used)) static unsigned long get_rate_uart(struct clk *clk)
{
	unsigned long pdr3 = __raw_readl(CCM_BASE + CCM_PDR3);
	unsigned long pdr4 = __raw_readl(CCM_BASE + CCM_PDR4);
	unsigned long div = get_3_3_div(pdr4 >> 10);

	if (pdr3 & (1 << 14))
		return get_rate_arm() / div;
	else
		return get_rate_ppll() / div;
}