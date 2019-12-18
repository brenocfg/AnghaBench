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
struct TYPE_2__ {scalar_t__ runtime_reg; } ;

/* Variables and functions */
 scalar_t__ WDT_TIME_OUT ; 
 scalar_t__ WDT_VAL ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 
 TYPE_1__ sch311x_wdt_data ; 

__attribute__((used)) static void sch311x_wdt_set_timeout(int t)
{
	unsigned char timeout_unit = 0x80;

	/* When new timeout is bigger then 255 seconds, we will use minutes */
	if (t > 255) {
		timeout_unit = 0;
		t /= 60;
	}

	/* -- Watchdog Timeout --
	 * Bit 0-6 (Reserved)
	 * Bit 7   WDT Time-out Value Units Select
	 *         (0 = Minutes, 1 = Seconds)
	 */
	outb(timeout_unit, sch311x_wdt_data.runtime_reg + WDT_TIME_OUT);

	/* -- Watchdog Timer Time-out Value --
	 * Bit 0-7 Binary coded units (0=Disabled, 1..255)
	 */
	outb(t, sch311x_wdt_data.runtime_reg + WDT_VAL);
}