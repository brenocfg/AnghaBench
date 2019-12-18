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
struct clk {int flags; unsigned long rate; } ;

/* Variables and functions */
 int CLK_HAS_RATE ; 

__attribute__((used)) static unsigned long mpc5121_clk_get_rate(struct clk *clk)
{
	if (clk->flags & CLK_HAS_RATE)
		return clk->rate;
	else
		return 0;
}