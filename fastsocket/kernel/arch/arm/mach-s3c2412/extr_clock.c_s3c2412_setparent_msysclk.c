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
 int /*<<< orphan*/  S3C2412_CLKSRC ; 
 unsigned long S3C2412_CLKSRC_MSYSCLK_MPLL ; 
 unsigned long __raw_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writel (unsigned long,int /*<<< orphan*/ ) ; 
 struct clk clk_mdivclk ; 
 struct clk clk_mpll ; 

__attribute__((used)) static int s3c2412_setparent_msysclk(struct clk *clk, struct clk *parent)
{
	unsigned long clksrc = __raw_readl(S3C2412_CLKSRC);

	if (parent == &clk_mdivclk)
		clksrc &= ~S3C2412_CLKSRC_MSYSCLK_MPLL;
	else if (parent == &clk_mpll)
		clksrc |= S3C2412_CLKSRC_MSYSCLK_MPLL;
	else
		return -EINVAL;

	clk->parent = parent;

	__raw_writel(clksrc, S3C2412_CLKSRC);
	return 0;
}