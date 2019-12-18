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
 int /*<<< orphan*/  rate_clk_init (struct clk*) ; 
 struct clk** rate_clks ; 

__attribute__((used)) static void rate_clks_init(void)
{
	struct clk **cpp, *clk;

	cpp = rate_clks;
	while ((clk = *cpp++))
		rate_clk_init(clk);
}