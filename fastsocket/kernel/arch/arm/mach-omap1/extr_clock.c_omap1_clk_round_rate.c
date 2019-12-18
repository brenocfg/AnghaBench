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
struct clk {int flags; long rate; long (* round_rate ) (struct clk*,unsigned long) ;} ;

/* Variables and functions */
 int RATE_FIXED ; 
 long stub1 (struct clk*,unsigned long) ; 

__attribute__((used)) static long omap1_clk_round_rate(struct clk *clk, unsigned long rate)
{
	if (clk->flags & RATE_FIXED)
		return clk->rate;

	if (clk->round_rate != NULL)
		return clk->round_rate(clk, rate);

	return clk->rate;
}