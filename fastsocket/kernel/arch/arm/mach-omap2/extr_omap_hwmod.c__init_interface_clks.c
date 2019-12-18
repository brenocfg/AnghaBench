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
struct omap_hwmod_ocp_if {struct clk* _clk; int /*<<< orphan*/  clkdev_con_id; int /*<<< orphan*/  clkdev_dev_id; } ;
struct omap_hwmod {int slaves_cnt; int /*<<< orphan*/  name; struct omap_hwmod_ocp_if** slaves; } ;
struct clk {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (struct clk*) ; 
 int /*<<< orphan*/  WARN (scalar_t__,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct clk* clk_get_sys (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int _init_interface_clks(struct omap_hwmod *oh)
{
	struct omap_hwmod_ocp_if *os;
	struct clk *c;
	int i;
	int ret = 0;

	if (oh->slaves_cnt == 0)
		return 0;

	for (i = 0, os = *oh->slaves; i < oh->slaves_cnt; i++, os++) {
		if (!os->clkdev_con_id)
			continue;

		c = clk_get_sys(os->clkdev_dev_id, os->clkdev_con_id);
		WARN(IS_ERR(c), "omap_hwmod: %s: cannot clk_get "
		     "interface_clk %s.%s\n", oh->name,
		     os->clkdev_dev_id, os->clkdev_con_id);
		if (IS_ERR(c))
			ret = -EINVAL;
		os->_clk = c;
	}

	return ret;
}