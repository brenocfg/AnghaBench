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
 scalar_t__ U300_WDOG_FR ; 
 int /*<<< orphan*/  U300_WDOG_FR_FEED_RESTART_TIMER ; 
 int /*<<< orphan*/  clk ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_enable (int /*<<< orphan*/ ) ; 
 scalar_t__ virtbase ; 
 int /*<<< orphan*/  writew (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void coh901327_keepalive(void)
{
	clk_enable(clk);
	/* Feed the watchdog */
	writew(U300_WDOG_FR_FEED_RESTART_TIMER,
	       virtbase + U300_WDOG_FR);
	clk_disable(clk);
}