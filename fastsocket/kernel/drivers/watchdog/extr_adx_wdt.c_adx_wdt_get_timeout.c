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
struct adx_wdt {int timeout; } ;

/* Variables and functions */

__attribute__((used)) static void adx_wdt_get_timeout(struct adx_wdt *wdt, unsigned long *seconds)
{
	*seconds = wdt->timeout / 1000;
}