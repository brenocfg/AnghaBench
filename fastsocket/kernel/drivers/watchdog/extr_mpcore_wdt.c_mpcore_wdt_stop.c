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
struct mpcore_wdt {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ TWD_WDOG_CONTROL ; 
 scalar_t__ TWD_WDOG_DISABLE ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wdt_lock ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void mpcore_wdt_stop(struct mpcore_wdt *wdt)
{
	spin_lock(&wdt_lock);
	writel(0x12345678, wdt->base + TWD_WDOG_DISABLE);
	writel(0x87654321, wdt->base + TWD_WDOG_DISABLE);
	writel(0x0, wdt->base + TWD_WDOG_CONTROL);
	spin_unlock(&wdt_lock);
}