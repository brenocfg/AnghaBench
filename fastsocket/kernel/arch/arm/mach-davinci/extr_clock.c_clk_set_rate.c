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
 int EINVAL ; 
 scalar_t__ IS_ERR (struct clk*) ; 

int clk_set_rate(struct clk *clk, unsigned long rate)
{
	if (clk == NULL || IS_ERR(clk))
		return -EINVAL;

	/* changing the clk rate is not supported */
	return -EINVAL;
}