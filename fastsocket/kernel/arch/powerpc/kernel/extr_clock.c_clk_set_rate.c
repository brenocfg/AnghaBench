#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct clk {int dummy; } ;
struct TYPE_2__ {int (* clk_set_rate ) (struct clk*,unsigned long) ;} ;

/* Variables and functions */
 int ENOSYS ; 
 TYPE_1__ clk_functions ; 
 int stub1 (struct clk*,unsigned long) ; 

int clk_set_rate(struct clk *clk, unsigned long rate)
{
	if (clk_functions.clk_set_rate)
		return clk_functions.clk_set_rate(clk, rate);
	return -ENOSYS;
}