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
struct clk {int /*<<< orphan*/  user_rate; struct clk* propagate_next; } ;

/* Variables and functions */
 int /*<<< orphan*/  local_set_rate (struct clk*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void propagate_rate(struct clk *clk)
{
	struct clk *tmp_clk;

	tmp_clk = clk;
	while (tmp_clk->propagate_next) {
		tmp_clk = tmp_clk->propagate_next;
		local_set_rate(tmp_clk, tmp_clk->user_rate);
	}
}