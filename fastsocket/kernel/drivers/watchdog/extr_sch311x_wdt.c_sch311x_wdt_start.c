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
struct TYPE_2__ {int /*<<< orphan*/  io_lock; scalar_t__ runtime_reg; } ;

/* Variables and functions */
 scalar_t__ GP60 ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 
 TYPE_1__ sch311x_wdt_data ; 
 int /*<<< orphan*/  sch311x_wdt_set_timeout (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timeout ; 

__attribute__((used)) static void sch311x_wdt_start(void)
{
	spin_lock(&sch311x_wdt_data.io_lock);

	/* set watchdog's timeout */
	sch311x_wdt_set_timeout(timeout);
	/* enable the watchdog */
	/* -- General Purpose I/O Bit 6.0 --
	 * Bit 0,   In/Out: 0 = Output, 1 = Input
	 * Bit 1,   Polarity: 0 = No Invert, 1 = Invert
	 * Bit 2-3, Function select: 00 = GPI/O, 01 = LED1, 11 = WDT,
	 *                           10 = Either Edge Triggered Intr.4
	 * Bit 4-6  (Reserved)
	 * Bit 7,   Output Type: 0 = Push Pull Bit, 1 = Open Drain
	 */
	outb(0x0e, sch311x_wdt_data.runtime_reg + GP60);

	spin_unlock(&sch311x_wdt_data.io_lock);

}