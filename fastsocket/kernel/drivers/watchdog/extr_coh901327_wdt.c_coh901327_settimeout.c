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

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ U300_WDOG_FR ; 
 int U300_WDOG_FR_FEED_RESTART_TIMER ; 
 scalar_t__ U300_WDOG_TR ; 
 int /*<<< orphan*/  clk ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_enable (int /*<<< orphan*/ ) ; 
 int margin ; 
 scalar_t__ virtbase ; 
 int /*<<< orphan*/  writew (int,scalar_t__) ; 

__attribute__((used)) static int coh901327_settimeout(int time)
{
	/*
	 * Max margin is 327 since the 10ms
	 * timeout register is max
	 * 0x7FFF = 327670ms ~= 327s.
	 */
	if (time <= 0 || time > 327)
		return -EINVAL;

	margin = time;
	clk_enable(clk);
	/* Set new timeout value */
	writew(margin * 100, virtbase + U300_WDOG_TR);
	/* Feed the dog */
	writew(U300_WDOG_FR_FEED_RESTART_TIMER,
	       virtbase + U300_WDOG_FR);
	clk_disable(clk);
	return 0;
}