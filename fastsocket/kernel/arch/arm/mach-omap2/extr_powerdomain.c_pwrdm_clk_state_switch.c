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
struct clk {int /*<<< orphan*/ * clkdm; } ;

/* Variables and functions */
 int EINVAL ; 
 int pwrdm_clkdm_state_switch (int /*<<< orphan*/ *) ; 

int pwrdm_clk_state_switch(struct clk *clk)
{
	if (clk != NULL && clk->clkdm != NULL)
		return pwrdm_clkdm_state_switch(clk->clkdm);
	return -EINVAL;
}