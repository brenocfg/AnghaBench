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
typedef  unsigned long u32 ;
struct clk {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  __calc_pre_post_dividers (unsigned long,unsigned long*,unsigned long*) ; 
 unsigned long clk_get_rate (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned long csi_round_rate(struct clk *clk, unsigned long rate)
{
	u32 pre, post, parent = clk_get_rate(clk->parent);
	u32 div = parent / rate;

	if (parent % rate)
		div++;

	__calc_pre_post_dividers(div, &pre, &post);

	return parent / (pre * post);
}