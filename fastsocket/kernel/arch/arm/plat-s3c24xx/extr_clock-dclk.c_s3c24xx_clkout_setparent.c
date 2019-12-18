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
struct clk {struct clk* parent; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned long S3C2410_MISCCR_CLK0_DCLK0 ; 
 unsigned long S3C2410_MISCCR_CLK0_FCLK ; 
 unsigned long S3C2410_MISCCR_CLK0_HCLK ; 
 unsigned long S3C2410_MISCCR_CLK0_MASK ; 
 unsigned long S3C2410_MISCCR_CLK0_MPLL ; 
 unsigned long S3C2410_MISCCR_CLK0_PCLK ; 
 unsigned long S3C2410_MISCCR_CLK0_UPLL ; 
 unsigned long S3C2410_MISCCR_CLK1_MASK ; 
 struct clk clk_f ; 
 struct clk clk_h ; 
 struct clk clk_mpll ; 
 struct clk clk_p ; 
 struct clk clk_upll ; 
 int /*<<< orphan*/  s3c2410_modify_misccr (unsigned long,unsigned long) ; 
 struct clk s3c24xx_clkout0 ; 
 struct clk s3c24xx_clkout1 ; 
 struct clk s3c24xx_dclk0 ; 
 struct clk s3c24xx_dclk1 ; 

__attribute__((used)) static int s3c24xx_clkout_setparent(struct clk *clk, struct clk *parent)
{
	unsigned long mask;
	unsigned long source;

	/* calculate the MISCCR setting for the clock */

	if (parent == &clk_mpll)
		source = S3C2410_MISCCR_CLK0_MPLL;
	else if (parent == &clk_upll)
		source = S3C2410_MISCCR_CLK0_UPLL;
	else if (parent == &clk_f)
		source = S3C2410_MISCCR_CLK0_FCLK;
	else if (parent == &clk_h)
		source = S3C2410_MISCCR_CLK0_HCLK;
	else if (parent == &clk_p)
		source = S3C2410_MISCCR_CLK0_PCLK;
	else if (clk == &s3c24xx_clkout0 && parent == &s3c24xx_dclk0)
		source = S3C2410_MISCCR_CLK0_DCLK0;
	else if (clk == &s3c24xx_clkout1 && parent == &s3c24xx_dclk1)
		source = S3C2410_MISCCR_CLK0_DCLK0;
	else
		return -EINVAL;

	clk->parent = parent;

	if (clk == &s3c24xx_clkout0)
		mask = S3C2410_MISCCR_CLK0_MASK;
	else {
		source <<= 4;
		mask = S3C2410_MISCCR_CLK1_MASK;
	}

	s3c2410_modify_misccr(mask, source);
	return 0;
}