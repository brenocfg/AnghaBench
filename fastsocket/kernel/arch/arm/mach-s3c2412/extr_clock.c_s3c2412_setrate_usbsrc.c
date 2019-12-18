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
 int /*<<< orphan*/  S3C2410_CLKDIVN ; 
 unsigned long S3C2412_CLKDIVN_USB48DIV ; 
 unsigned long __raw_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writel (unsigned long,int /*<<< orphan*/ ) ; 
 unsigned long clk_get_rate (int /*<<< orphan*/ ) ; 
 unsigned long s3c2412_roundrate_usbsrc (struct clk*,unsigned long) ; 

__attribute__((used)) static int s3c2412_setrate_usbsrc(struct clk *clk, unsigned long rate)
{
	unsigned long parent_rate = clk_get_rate(clk->parent);
	unsigned long clkdivn = __raw_readl(S3C2410_CLKDIVN);

	rate = s3c2412_roundrate_usbsrc(clk, rate);

	if ((parent_rate / rate) == 2)
		clkdivn |= S3C2412_CLKDIVN_USB48DIV;
	else
		clkdivn &= ~S3C2412_CLKDIVN_USB48DIV;

	__raw_writel(clkdivn, S3C2410_CLKDIVN);
	return 0;
}