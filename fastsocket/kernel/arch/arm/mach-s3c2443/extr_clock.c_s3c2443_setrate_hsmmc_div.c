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
 int /*<<< orphan*/  S3C2443_CLKDIV1 ; 
 unsigned long S3C2443_CLKDIV1_HSMMCDIV_MASK ; 
 unsigned long S3C2443_CLKDIV1_HSMMCDIV_SHIFT ; 
 unsigned long __raw_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writel (unsigned long,int /*<<< orphan*/ ) ; 
 unsigned long clk_get_rate (int /*<<< orphan*/ ) ; 
 unsigned long s3c2443_roundrate_clksrc4 (struct clk*,unsigned long) ; 

__attribute__((used)) static int s3c2443_setrate_hsmmc_div(struct clk *clk, unsigned long rate)
{
	unsigned long parent_rate = clk_get_rate(clk->parent);
	unsigned long clkdivn = __raw_readl(S3C2443_CLKDIV1);

	rate = s3c2443_roundrate_clksrc4(clk, rate);
	rate = parent_rate / rate;

	clkdivn &= ~S3C2443_CLKDIV1_HSMMCDIV_MASK;
	clkdivn |= (rate - 1) << S3C2443_CLKDIV1_HSMMCDIV_SHIFT;

	__raw_writel(clkdivn, S3C2443_CLKDIV1);
	return 0;
}