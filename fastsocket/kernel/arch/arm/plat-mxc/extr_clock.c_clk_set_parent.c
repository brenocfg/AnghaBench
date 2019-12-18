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
 int EINVAL ; 
 scalar_t__ IS_ERR (struct clk*) ; 
 int /*<<< orphan*/  clocks_mutex ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (struct clk*,struct clk*) ; 

int clk_set_parent(struct clk *clk, struct clk *parent)
{
	int ret = -EINVAL;

	if (clk == NULL || IS_ERR(clk) || parent == NULL ||
	    IS_ERR(parent) || clk->set_parent == NULL)
		return ret;

	mutex_lock(&clocks_mutex);
	ret = clk->set_parent(clk, parent);
	if (ret == 0)
		clk->parent = parent;
	mutex_unlock(&clocks_mutex);

	return ret;
}