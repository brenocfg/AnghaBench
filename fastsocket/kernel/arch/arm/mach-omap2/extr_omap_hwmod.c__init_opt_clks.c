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
struct omap_hwmod_opt_clk {struct clk* _clk; int /*<<< orphan*/  clkdev_con_id; int /*<<< orphan*/  clkdev_dev_id; } ;
struct omap_hwmod {int opt_clks_cnt; int /*<<< orphan*/  name; struct omap_hwmod_opt_clk* opt_clks; } ;
struct clk {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (struct clk*) ; 
 int /*<<< orphan*/  WARN (scalar_t__,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct clk* clk_get_sys (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int _init_opt_clks(struct omap_hwmod *oh)
{
	struct omap_hwmod_opt_clk *oc;
	struct clk *c;
	int i;
	int ret = 0;

	for (i = oh->opt_clks_cnt, oc = oh->opt_clks; i > 0; i--, oc++) {
		c = clk_get_sys(oc->clkdev_dev_id, oc->clkdev_con_id);
		WARN(IS_ERR(c), "omap_hwmod: %s: cannot clk_get opt_clk "
		     "%s.%s\n", oh->name, oc->clkdev_dev_id,
		     oc->clkdev_con_id);
		if (IS_ERR(c))
			ret = -EINVAL;
		oc->_clk = c;
	}

	return ret;
}