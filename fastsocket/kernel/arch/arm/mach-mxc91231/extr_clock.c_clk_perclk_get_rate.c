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
typedef  int u32 ;
struct clk {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  MXC_CRMAP_ACDER2 ; 
 int MXC_CRMAP_ACDER2_BAUD_ISEL_MASK ; 
 int __raw_readl (int /*<<< orphan*/ ) ; 
 unsigned long clk_get_rate (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned long clk_perclk_get_rate(struct clk *clk)
{
	u32 acder2;

	acder2 = __raw_readl(MXC_CRMAP_ACDER2);
	if (acder2 & MXC_CRMAP_ACDER2_BAUD_ISEL_MASK)
		return 2 * clk_get_rate(clk->parent);

	return clk_get_rate(clk->parent);
}