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
struct clk {unsigned long rate; int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned long S3C2410_DCLKCON_DCLK0_CMP (unsigned long) ; 
 unsigned long S3C2410_DCLKCON_DCLK0_CMP_MASK ; 
 unsigned long S3C2410_DCLKCON_DCLK0_DIV (unsigned long) ; 
 unsigned long S3C2410_DCLKCON_DCLK0_DIV_MASK ; 
 unsigned long S3C2410_DCLKCON_DCLK1_CMP (unsigned long) ; 
 unsigned long S3C2410_DCLKCON_DCLK1_CMP_MASK ; 
 unsigned long S3C2410_DCLKCON_DCLK1_DIV (unsigned long) ; 
 unsigned long S3C2410_DCLKCON_DCLK1_DIV_MASK ; 
 int /*<<< orphan*/  S3C24XX_DCLKCON ; 
 unsigned long __raw_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writel (unsigned long,int /*<<< orphan*/ ) ; 
 unsigned long clk_get_rate (int /*<<< orphan*/ ) ; 
 unsigned long s3c24xx_calc_div (struct clk*,unsigned long) ; 
 struct clk s3c24xx_dclk0 ; 
 struct clk s3c24xx_dclk1 ; 

__attribute__((used)) static int s3c24xx_set_dclk_rate(struct clk *clk, unsigned long rate)
{
	unsigned long mask, data, div = s3c24xx_calc_div(clk, rate);

	if (div == 0)
		return -EINVAL;

	if (clk == &s3c24xx_dclk0) {
		mask = S3C2410_DCLKCON_DCLK0_DIV_MASK |
			S3C2410_DCLKCON_DCLK0_CMP_MASK;
		data = S3C2410_DCLKCON_DCLK0_DIV(div) |
			S3C2410_DCLKCON_DCLK0_CMP((div + 1) / 2);
	} else if (clk == &s3c24xx_dclk1) {
		mask = S3C2410_DCLKCON_DCLK1_DIV_MASK |
			S3C2410_DCLKCON_DCLK1_CMP_MASK;
		data = S3C2410_DCLKCON_DCLK1_DIV(div) |
			S3C2410_DCLKCON_DCLK1_CMP((div + 1) / 2);
	} else
		return -EINVAL;

	clk->rate = clk_get_rate(clk->parent) / div;
	__raw_writel(((__raw_readl(S3C24XX_DCLKCON) & ~mask) | data),
		S3C24XX_DCLKCON);
	return clk->rate;
}