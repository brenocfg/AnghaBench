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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  RSTOUTn_MASK ; 
 int /*<<< orphan*/  TIMER_CTRL ; 
 int /*<<< orphan*/  WDT_EN ; 
 int /*<<< orphan*/  WDT_RESET_OUT_EN ; 
 int /*<<< orphan*/  readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wdt_lock ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void orion_wdt_disable(void)
{
	u32 reg;

	spin_lock(&wdt_lock);

	/* Disable reset on watchdog */
	reg = readl(RSTOUTn_MASK);
	reg &= ~WDT_RESET_OUT_EN;
	writel(reg, RSTOUTn_MASK);

	/* Disable watchdog timer */
	reg = readl(TIMER_CTRL);
	reg &= ~WDT_EN;
	writel(reg, TIMER_CTRL);

	spin_unlock(&wdt_lock);
}