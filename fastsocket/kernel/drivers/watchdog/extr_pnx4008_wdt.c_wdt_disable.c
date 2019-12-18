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
 int /*<<< orphan*/  WDTIM_CTRL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_set_rate (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  io_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wdt_base ; 
 scalar_t__ wdt_clk ; 

__attribute__((used)) static void wdt_disable(void)
{
	spin_lock(&io_lock);

	__raw_writel(0, WDTIM_CTRL(wdt_base));	/*stop counter */
	if (wdt_clk)
		clk_set_rate(wdt_clk, 0);

	spin_unlock(&io_lock);
}