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
 int /*<<< orphan*/  inb_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wafwdt_lock ; 
 int /*<<< orphan*/  wdt_start ; 
 int /*<<< orphan*/  wdt_stop ; 

__attribute__((used)) static void wafwdt_ping(void)
{
	/* pat watchdog */
	spin_lock(&wafwdt_lock);
	inb_p(wdt_stop);
	inb_p(wdt_start);
	spin_unlock(&wafwdt_lock);
}