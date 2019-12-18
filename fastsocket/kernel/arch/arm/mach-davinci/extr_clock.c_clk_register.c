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
struct clk {TYPE_1__* parent; scalar_t__ rate; int /*<<< orphan*/  node; int /*<<< orphan*/  name; } ;
struct TYPE_2__ {scalar_t__ rate; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (struct clk*) ; 
 scalar_t__ WARN (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clocks ; 
 int /*<<< orphan*/  clocks_mutex ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int clk_register(struct clk *clk)
{
	if (clk == NULL || IS_ERR(clk))
		return -EINVAL;

	if (WARN(clk->parent && !clk->parent->rate,
			"CLK: %s parent %s has no rate!\n",
			clk->name, clk->parent->name))
		return -EINVAL;

	mutex_lock(&clocks_mutex);
	list_add_tail(&clk->node, &clocks);
	mutex_unlock(&clocks_mutex);

	/* If rate is already set, use it */
	if (clk->rate)
		return 0;

	/* Otherwise, default to parent rate */
	if (clk->parent)
		clk->rate = clk->parent->rate;

	return 0;
}