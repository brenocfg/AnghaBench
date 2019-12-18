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
struct omap_dm_timer {scalar_t__ enabled; int /*<<< orphan*/  fclk; int /*<<< orphan*/  iclk; } ;

/* Variables and functions */
 int /*<<< orphan*/  omap_dm_clk_disable (int /*<<< orphan*/ ) ; 

void omap_dm_timer_disable(struct omap_dm_timer *timer)
{
	if (!timer->enabled)
		return;

	omap_dm_clk_disable(timer->iclk);
	omap_dm_clk_disable(timer->fclk);

	timer->enabled = 0;
}