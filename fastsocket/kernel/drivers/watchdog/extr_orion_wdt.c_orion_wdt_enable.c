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
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  BRIDGE_CAUSE ; 
 int /*<<< orphan*/  RSTOUTn_MASK ; 
 int /*<<< orphan*/  TIMER_CTRL ; 
 int WDT_EN ; 
 int WDT_INT_REQ ; 
 int WDT_RESET_OUT_EN ; 
 int /*<<< orphan*/  WDT_VAL ; 
 int heartbeat ; 
 int readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wdt_lock ; 
 int wdt_tclk ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void orion_wdt_enable(void)
{
	u32 reg;

	spin_lock(&wdt_lock);

	/* Set watchdog duration */
	writel(wdt_tclk * heartbeat, WDT_VAL);

	/* Clear watchdog timer interrupt */
	reg = readl(BRIDGE_CAUSE);
	reg &= ~WDT_INT_REQ;
	writel(reg, BRIDGE_CAUSE);

	/* Enable watchdog timer */
	reg = readl(TIMER_CTRL);
	reg |= WDT_EN;
	writel(reg, TIMER_CTRL);

	/* Enable reset on watchdog */
	reg = readl(RSTOUTn_MASK);
	reg |= WDT_RESET_OUT_EN;
	writel(reg, RSTOUTn_MASK);

	spin_unlock(&wdt_lock);
}