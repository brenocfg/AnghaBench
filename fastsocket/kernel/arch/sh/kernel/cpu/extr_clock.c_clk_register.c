#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ prev; scalar_t__ next; } ;
struct clk {TYPE_2__* ops; TYPE_3__ node; TYPE_3__ sibling; TYPE_1__* parent; scalar_t__ usecount; int /*<<< orphan*/  children; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* init ) (struct clk*) ;} ;
struct TYPE_4__ {int /*<<< orphan*/  children; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_ERR (struct clk*) ; 
 int /*<<< orphan*/  clock_list ; 
 int /*<<< orphan*/  clock_list_sem ; 
 int /*<<< orphan*/  list_add (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  root_clks ; 
 int /*<<< orphan*/  stub1 (struct clk*) ; 

int clk_register(struct clk *clk)
{
	if (clk == NULL || IS_ERR(clk))
		return -EINVAL;

	/*
	 * trap out already registered clocks
	 */
	if (clk->node.next || clk->node.prev)
		return 0;

	mutex_lock(&clock_list_sem);

	INIT_LIST_HEAD(&clk->children);
	clk->usecount = 0;

	if (clk->parent)
		list_add(&clk->sibling, &clk->parent->children);
	else
		list_add(&clk->sibling, &root_clks);

	list_add(&clk->node, &clock_list);
	if (clk->ops && clk->ops->init)
		clk->ops->init(clk);
	mutex_unlock(&clock_list_sem);

	return 0;
}