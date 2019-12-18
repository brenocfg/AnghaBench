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
struct omap_hwmod_ocp_if {int flags; struct clk* _clk; } ;
struct omap_hwmod {int slaves_cnt; struct omap_hwmod_ocp_if** slaves; struct clk* _clk; int /*<<< orphan*/  name; } ;
struct clk {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (struct clk*) ; 
 int OCPIF_SWSUP_IDLE ; 
 int /*<<< orphan*/  clk_disable (struct clk*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int _disable_clocks(struct omap_hwmod *oh)
{
	struct omap_hwmod_ocp_if *os;
	int i;

	pr_debug("omap_hwmod: %s: disabling clocks\n", oh->name);

	if (oh->_clk && !IS_ERR(oh->_clk))
		clk_disable(oh->_clk);

	if (oh->slaves_cnt > 0) {
		for (i = 0, os = *oh->slaves; i < oh->slaves_cnt; i++, os++) {
			struct clk *c = os->_clk;

			if (c && !IS_ERR(c) && (os->flags & OCPIF_SWSUP_IDLE))
				clk_disable(c);
		}
	}

	/* The opt clocks are controlled by the device driver. */

	return 0;
}