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
struct clk {TYPE_1__* ops; } ;
struct TYPE_2__ {long (* round_rate ) (struct clk*,unsigned long) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  clk_good (struct clk*) ; 
 long stub1 (struct clk*,unsigned long) ; 
 scalar_t__ unlikely (int) ; 

long clk_round_rate(struct clk *clk, unsigned long rate)
{
	if (unlikely(!clk_good(clk)))
		return 0;

	if (clk->ops->round_rate)
		return clk->ops->round_rate(clk, rate);

	return 0;
}