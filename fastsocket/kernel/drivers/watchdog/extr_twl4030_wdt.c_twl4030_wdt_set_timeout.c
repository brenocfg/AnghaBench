#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct twl4030_wdt {int timer_margin; TYPE_1__ miscdev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int twl4030_wdt_enable (struct twl4030_wdt*) ; 

__attribute__((used)) static int twl4030_wdt_set_timeout(struct twl4030_wdt *wdt, int timeout)
{
	if (timeout < 0 || timeout > 30) {
		dev_warn(wdt->miscdev.parent,
			"Timeout can only be in the range [0-30] seconds");
		return -EINVAL;
	}
	wdt->timer_margin = timeout;
	return twl4030_wdt_enable(wdt);
}