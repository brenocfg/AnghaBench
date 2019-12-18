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
typedef  scalar_t__ u32 ;
struct clk {int rate; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_reg_disable (struct clk*) ; 
 int /*<<< orphan*/  clk_reg_enable (struct clk*) ; 

__attribute__((used)) static int on_off_inv_set_rate(struct clk *clk, u32 rate)
{
	if (rate) {
		clk_reg_disable(clk);	/*enable bit is inverted */
		clk->rate = 1;
	} else {
		clk_reg_enable(clk);
		clk->rate = 0;
	}
	return 0;
}