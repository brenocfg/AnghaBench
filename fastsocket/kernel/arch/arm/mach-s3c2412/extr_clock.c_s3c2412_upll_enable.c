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
 int /*<<< orphan*/  S3C2410_UPLLCON ; 
 unsigned long S3C2412_PLLCON_OFF ; 
 unsigned long __raw_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writel (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int s3c2412_upll_enable(struct clk *clk, int enable)
{
	unsigned long upllcon = __raw_readl(S3C2410_UPLLCON);
	unsigned long orig = upllcon;

	if (!enable)
		upllcon |= S3C2412_PLLCON_OFF;
	else
		upllcon &= ~S3C2412_PLLCON_OFF;

	__raw_writel(upllcon, S3C2410_UPLLCON);

	/* allow ~150uS for the PLL to settle and lock */

	if (enable && (orig & S3C2412_PLLCON_OFF))
		udelay(150);

	return 0;
}