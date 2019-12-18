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
struct clk {int id; } ;

/* Variables and functions */
 scalar_t__ CCM_BASE ; 
 scalar_t__ CCM_PDR2 ; 
 unsigned long __raw_readl (scalar_t__) ; 
 unsigned long get_rate_arm () ; 
 unsigned long get_rate_ppll () ; 

__attribute__((used)) static unsigned long get_rate_ssi(struct clk *clk)
{
	unsigned long pdr2 = __raw_readl(CCM_BASE + CCM_PDR2);
	unsigned long div1, div2, rate;

	if (pdr2 & (1 << 6))
		rate = get_rate_arm();
	else
		rate = get_rate_ppll();

	switch (clk->id) {
	default:
	case 0:
		div1 = pdr2 & 0x3f;
		div2 = (pdr2 >> 24) & 0x7;
		break;
	case 1:
		div1 = (pdr2 >> 8) & 0x3f;
		div2 = (pdr2 >> 27) & 0x7;
		break;
	}

	return rate / ((div1 + 1) * (div2 + 1));
}