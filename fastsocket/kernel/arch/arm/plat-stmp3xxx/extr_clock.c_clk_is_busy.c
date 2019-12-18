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
struct clk {int busy_bit; int /*<<< orphan*/  busy_reg; } ;

/* Variables and functions */
 int __raw_readl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int clk_is_busy(struct clk *clk)
{
	return __raw_readl(clk->busy_reg) & (1 << clk->busy_bit);
}