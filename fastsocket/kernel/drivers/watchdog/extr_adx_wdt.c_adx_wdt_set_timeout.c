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
struct adx_wdt {unsigned int state; unsigned long timeout; int /*<<< orphan*/  lock; scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ ADX_WDT_TIMEOUT ; 
 unsigned int WDT_STATE_START ; 
 int /*<<< orphan*/  adx_wdt_start_locked (struct adx_wdt*) ; 
 int /*<<< orphan*/  adx_wdt_stop_locked (struct adx_wdt*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writel (unsigned long,scalar_t__) ; 

__attribute__((used)) static void adx_wdt_set_timeout(struct adx_wdt *wdt, unsigned long seconds)
{
	unsigned long timeout = seconds * 1000;
	unsigned long flags;
	unsigned int state;

	spin_lock_irqsave(&wdt->lock, flags);
	state = wdt->state;
	adx_wdt_stop_locked(wdt);
	writel(timeout, wdt->base + ADX_WDT_TIMEOUT);

	if (state == WDT_STATE_START)
		adx_wdt_start_locked(wdt);

	wdt->timeout = timeout;
	spin_unlock_irqrestore(&wdt->lock, flags);
}