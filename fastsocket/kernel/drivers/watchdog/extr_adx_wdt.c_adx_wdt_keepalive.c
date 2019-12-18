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
struct adx_wdt {int /*<<< orphan*/  lock; scalar_t__ base; int /*<<< orphan*/  timeout; } ;

/* Variables and functions */
 scalar_t__ ADX_WDT_TIMEOUT ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void adx_wdt_keepalive(struct adx_wdt *wdt)
{
	unsigned long flags;

	spin_lock_irqsave(&wdt->lock, flags);
	writel(wdt->timeout, wdt->base + ADX_WDT_TIMEOUT);
	spin_unlock_irqrestore(&wdt->lock, flags);
}