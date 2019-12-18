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
struct mpc5200_wdt {int count; int ipb_freq; } ;

/* Variables and functions */

__attribute__((used)) static void mpc5200_wdt_set_timeout(struct mpc5200_wdt *wdt, int timeout)
{
	/* use biggest prescaler of 64k */
	wdt->count = (wdt->ipb_freq + 0xffff) / 0x10000 * timeout;

	if (wdt->count > 0xffff)
		wdt->count = 0xffff;
}