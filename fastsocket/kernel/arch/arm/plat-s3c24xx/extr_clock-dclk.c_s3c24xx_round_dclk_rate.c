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
 unsigned long clk_get_rate (int /*<<< orphan*/ ) ; 
 unsigned long s3c24xx_calc_div (struct clk*,unsigned long) ; 

__attribute__((used)) static unsigned long s3c24xx_round_dclk_rate(struct clk *clk,
	unsigned long rate)
{
	unsigned long div = s3c24xx_calc_div(clk, rate);

	if (div == 0)
		return 0;

	return clk_get_rate(clk->parent) / div;
}