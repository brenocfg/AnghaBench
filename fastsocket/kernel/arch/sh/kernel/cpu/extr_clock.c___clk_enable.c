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
struct clk {int /*<<< orphan*/  usecount; struct clk* parent; TYPE_1__* ops; } ;
struct TYPE_2__ {int (* enable ) (struct clk*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  __clk_disable (struct clk*) ; 
 int stub1 (struct clk*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int __clk_enable(struct clk *clk)
{
	int ret = 0;

	if (clk->usecount++ == 0) {
		if (clk->parent) {
			ret = __clk_enable(clk->parent);
			if (unlikely(ret))
				goto err;
		}

		if (clk->ops && clk->ops->enable) {
			ret = clk->ops->enable(clk);
			if (ret) {
				if (clk->parent)
					__clk_disable(clk->parent);
				goto err;
			}
		}
	}

	return ret;
err:
	clk->usecount--;
	return ret;
}