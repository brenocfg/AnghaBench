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
 int /*<<< orphan*/  WDT_RT ; 
 unsigned short inb_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wdt_lock ; 

__attribute__((used)) static int wdt_get_temperature(void)
{
	unsigned short c;
	unsigned long flags;

	spin_lock_irqsave(&wdt_lock, flags);
	c = inb_p(WDT_RT);
	spin_unlock_irqrestore(&wdt_lock, flags);
	return (c * 11 / 15) + 7;
}