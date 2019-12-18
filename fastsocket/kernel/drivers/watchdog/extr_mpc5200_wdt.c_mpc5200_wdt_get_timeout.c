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

__attribute__((used)) static int mpc5200_wdt_get_timeout(struct mpc5200_wdt *wdt)
{
	return wdt->count * 0x10000 / wdt->ipb_freq;
}