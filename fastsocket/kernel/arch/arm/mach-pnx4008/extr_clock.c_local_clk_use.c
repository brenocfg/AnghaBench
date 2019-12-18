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
struct clk {int /*<<< orphan*/  usecount; struct clk* parent; } ;

/* Variables and functions */
 int local_clk_enable (struct clk*) ; 
 int /*<<< orphan*/  local_clk_unuse (struct clk*) ; 

__attribute__((used)) static int local_clk_use(struct clk *clk)
{
	int ret = 0;
	if (clk->usecount++ == 0) {
		if (clk->parent)
			ret = local_clk_use(clk->parent);

		if (ret != 0) {
			clk->usecount--;
			goto out;
		}

		ret = local_clk_enable(clk);

		if (ret != 0 && clk->parent) {
			local_clk_unuse(clk->parent);
			clk->usecount--;
		}
	}
out:
	return ret;
}