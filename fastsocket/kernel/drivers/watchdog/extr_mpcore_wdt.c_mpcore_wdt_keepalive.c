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
struct mpcore_wdt {int perturb; scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ TWD_WDOG_LOAD ; 
 int mpcore_margin ; 
 int mpcore_timer_rate ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wdt_lock ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void mpcore_wdt_keepalive(struct mpcore_wdt *wdt)
{
	unsigned int count;

	/* Assume prescale is set to 256 */
	count = (mpcore_timer_rate / 256) * mpcore_margin;

	/* Reload the counter */
	spin_lock(&wdt_lock);
	writel(count + wdt->perturb, wdt->base + TWD_WDOG_LOAD);
	wdt->perturb = wdt->perturb ? 0 : 1;
	spin_unlock(&wdt_lock);
}