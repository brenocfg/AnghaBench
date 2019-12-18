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
struct clk {unsigned int ctrlbit; } ;

/* Variables and functions */
 int /*<<< orphan*/  S3C2443_PCLKCON ; 
 unsigned long __raw_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writel (unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int s3c2443_clkcon_enable_p(struct clk *clk, int enable)
{
	unsigned int clocks = clk->ctrlbit;
	unsigned long clkcon;

	clkcon = __raw_readl(S3C2443_PCLKCON);

	if (enable)
		clkcon |= clocks;
	else
		clkcon &= ~clocks;

	__raw_writel(clkcon, S3C2443_PCLKCON);

	return 0;
}