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
struct adx_wdt {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  adx_wdt_start_locked (struct adx_wdt*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void adx_wdt_start(struct adx_wdt *wdt)
{
	unsigned long flags;

	spin_lock_irqsave(&wdt->lock, flags);
	adx_wdt_start_locked(wdt);
	spin_unlock_irqrestore(&wdt->lock, flags);
}