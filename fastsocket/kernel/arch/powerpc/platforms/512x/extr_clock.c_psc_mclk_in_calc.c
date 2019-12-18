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
struct clk {int rate; } ;

/* Variables and functions */
 int devtree_getfreq (char*) ; 

__attribute__((used)) static void psc_mclk_in_calc(struct clk *clk)
{
	clk->rate = devtree_getfreq("psc_mclk_in");
	if (!clk->rate)
		clk->rate = 25000000;
}