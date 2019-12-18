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
struct clk {scalar_t__ usage; struct clk* parent; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  S3C2443_SCLKCON ; 
 unsigned long S3C2443_SCLKCON_HSMMCCLK_EPLL ; 
 unsigned long S3C2443_SCLKCON_HSMMCCLK_EXT ; 
 unsigned long __raw_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writel (unsigned long,int /*<<< orphan*/ ) ; 
 struct clk clk_epll ; 
 struct clk clk_ext ; 

__attribute__((used)) static int s3c2443_setparent_hsmmc(struct clk *clk, struct clk *parent)
{
	unsigned long clksrc = __raw_readl(S3C2443_SCLKCON);

	clksrc &= ~(S3C2443_SCLKCON_HSMMCCLK_EXT |
		    S3C2443_SCLKCON_HSMMCCLK_EPLL);

	if (parent == &clk_epll)
		clksrc |= S3C2443_SCLKCON_HSMMCCLK_EPLL;
	else if (parent == &clk_ext)
		clksrc |= S3C2443_SCLKCON_HSMMCCLK_EXT;
	else
		return -EINVAL;

	if (clk->usage > 0) {
		__raw_writel(clksrc, S3C2443_SCLKCON);
	}

	clk->parent = parent;
	return 0;
}