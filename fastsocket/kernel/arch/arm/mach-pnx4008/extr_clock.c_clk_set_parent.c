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
struct clk {int (* set_parent ) (struct clk*,struct clk*) ;struct clk* parent; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  clock_lock () ; 
 int /*<<< orphan*/  clock_unlock () ; 
 int stub1 (struct clk*,struct clk*) ; 

int clk_set_parent(struct clk *clk, struct clk *parent)
{
	int ret = -ENODEV;
	if (!clk->set_parent)
		goto out;

	clock_lock();
	ret = clk->set_parent(clk, parent);
	if (!ret)
		clk->parent = parent;
	clock_unlock();

out:
	return ret;
}