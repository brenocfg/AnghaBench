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
struct clk {unsigned long ctrlbit; } ;

/* Variables and functions */
 int /*<<< orphan*/  S3C24XX_DCLKCON ; 
 unsigned long __raw_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writel (unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int s3c24xx_dclk_enable(struct clk *clk, int enable)
{
	unsigned long dclkcon = __raw_readl(S3C24XX_DCLKCON);

	if (enable)
		dclkcon |= clk->ctrlbit;
	else
		dclkcon &= ~clk->ctrlbit;

	__raw_writel(dclkcon, S3C24XX_DCLKCON);

	return 0;
}