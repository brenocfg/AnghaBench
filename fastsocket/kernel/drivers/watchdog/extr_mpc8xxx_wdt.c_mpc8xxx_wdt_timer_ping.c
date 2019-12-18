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
 int HZ ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  mpc8xxx_wdt_keepalive () ; 
 int timeout_sec ; 
 int /*<<< orphan*/  wdt_timer ; 

__attribute__((used)) static void mpc8xxx_wdt_timer_ping(unsigned long arg)
{
	mpc8xxx_wdt_keepalive();
	/* We're pinging it twice faster than needed, just to be sure. */
	mod_timer(&wdt_timer, jiffies + HZ * timeout_sec / 2);
}