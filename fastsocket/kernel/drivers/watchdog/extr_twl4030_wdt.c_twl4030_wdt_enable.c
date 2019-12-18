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
struct twl4030_wdt {scalar_t__ timer_margin; } ;

/* Variables and functions */
 int twl4030_wdt_write (scalar_t__) ; 

__attribute__((used)) static int twl4030_wdt_enable(struct twl4030_wdt *wdt)
{
	return twl4030_wdt_write(wdt->timer_margin + 1);
}