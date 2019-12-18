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
struct clk {scalar_t__ usage; struct clk* parent; int /*<<< orphan*/  (* enable ) (struct clk*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct clk*) ; 
 int /*<<< orphan*/  clocks_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct clk*,int /*<<< orphan*/ ) ; 

void clk_disable(struct clk *clk)
{
	if (IS_ERR(clk) || clk == NULL)
		return;

	spin_lock(&clocks_lock);

	if ((--clk->usage) == 0)
		(clk->enable)(clk, 0);

	spin_unlock(&clocks_lock);
	clk_disable(clk->parent);
}