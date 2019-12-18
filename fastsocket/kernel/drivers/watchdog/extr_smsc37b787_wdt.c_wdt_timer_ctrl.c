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
 int /*<<< orphan*/  write_io_cr (int,unsigned char) ; 

__attribute__((used)) static inline void wdt_timer_ctrl(unsigned char reg)
{
	/* -- Watchdog timer control --
	 * Bit 0   Status Bit: 0 = Timer counting, 1 = Timeout occured
	 * Bit 1   Power LED Toggle: 0 = Disable Toggle, 1 = Toggle at 1 Hz
	 * Bit 2   Force Timeout: 1 = Forces WD timeout event (self-cleaning)
	 * Bit 3   P20 Force Timeout enabled:
	 *          0 = P20 activity does not generate the WD timeout event
	 *          1 = P20 Allows rising edge of P20, from the keyboard
	 *              controller, to force the WD timeout event.
	 * Bit 4   (Reserved)
	 * -- Soft power management --
	 * Bit 5   Stop Counter: 1 = Stop software power down counter
	 *            set via register 0xB8, (self-cleaning)
	 *            (Upon read: 0 = Counter running, 1 = Counter stopped)
	 * Bit 6   Restart Counter: 1 = Restart software power down counter
	 *            set via register 0xB8, (self-cleaning)
	 * Bit 7   SPOFF: 1 = Force software power down (self-cleaning)
	 */
	write_io_cr(0xF4, reg);
}