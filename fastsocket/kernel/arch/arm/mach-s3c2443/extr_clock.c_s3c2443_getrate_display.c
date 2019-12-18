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
 unsigned long S3C2443_CLKDIV1_DISPDIV_MASK ; 
 unsigned long S3C2443_CLKDIV1_DISPDIV_SHIFT ; 
 unsigned long __raw_readl (int /*<<< orphan*/ ) ; 
 unsigned long clk_get_rate (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned long s3c2443_getrate_display(struct clk *clk)
{
	unsigned long parent_rate = clk_get_rate(clk->parent);
	unsigned long div = __raw_readl(S3C2443_CLKDIV1);

	div &= S3C2443_CLKDIV1_DISPDIV_MASK;
	div >>= S3C2443_CLKDIV1_DISPDIV_SHIFT;

	return parent_rate / (div + 1);
}