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
struct clk {int /*<<< orphan*/  (* disable ) (struct clk*) ;int /*<<< orphan*/  usecount; struct clk* secondary; struct clk* parent; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct clk*) ; 
 int /*<<< orphan*/  stub1 (struct clk*) ; 

__attribute__((used)) static void __clk_disable(struct clk *clk)
{
	if (clk == NULL || IS_ERR(clk))
		return;

	__clk_disable(clk->parent);
	__clk_disable(clk->secondary);

	if (!(--clk->usecount) && clk->disable)
		clk->disable(clk);
}