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
 int /*<<< orphan*/  app_timer_clk ; 
 int /*<<< orphan*/  clk_enable (int /*<<< orphan*/ *) ; 

void u300_enable_timer_clock(void)
{
	clk_enable(&app_timer_clk);
}