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
struct clk {scalar_t__ users; struct clk* parent; int /*<<< orphan*/  (* mode ) (struct clk*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  stub1 (struct clk*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __clk_disable(struct clk *clk)
{
	BUG_ON(clk->users == 0);
	if (--clk->users == 0 && clk->mode)
		clk->mode(clk, 0);
	if (clk->parent)
		__clk_disable(clk->parent);
}