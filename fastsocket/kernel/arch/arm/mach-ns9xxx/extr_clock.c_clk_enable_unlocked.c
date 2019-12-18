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
struct clk {int (* endisable ) (struct clk*,int) ;int /*<<< orphan*/  usage; struct clk* parent; } ;

/* Variables and functions */
 int stub1 (struct clk*,int) ; 

__attribute__((used)) static int clk_enable_unlocked(struct clk *clk)
{
	int ret = 0;
	if (clk->parent) {
		ret = clk_enable_unlocked(clk->parent);
		if (ret)
			return ret;
	}

	if (clk->usage++ == 0 && clk->endisable)
		ret = clk->endisable(clk, 1);

	return ret;
}