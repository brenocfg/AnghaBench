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
 int /*<<< orphan*/  CCM_PCDR0 ; 
 int __raw_readl (int /*<<< orphan*/ ) ; 
 unsigned long get_rate_ssix (struct clk*,int) ; 

__attribute__((used)) static unsigned long get_rate_ssi2(struct clk *clk)
{
	return get_rate_ssix(clk, (__raw_readl(CCM_PCDR0) >> 26) & 0x3f);
}