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
struct omap_dm_timer {int /*<<< orphan*/  fclk; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  __delay (int) ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_enable (int /*<<< orphan*/ ) ; 
 int clk_set_parent (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * dm_source_clocks ; 

int omap_dm_timer_set_source(struct omap_dm_timer *timer, int source)
{
	int ret = -EINVAL;

	if (source < 0 || source >= 3)
		return -EINVAL;

	clk_disable(timer->fclk);
	ret = clk_set_parent(timer->fclk, dm_source_clocks[source]);
	clk_enable(timer->fclk);

	/*
	 * When the functional clock disappears, too quick writes seem
	 * to cause an abort. XXX Is this still necessary?
	 */
	__delay(150000);

	return ret;
}