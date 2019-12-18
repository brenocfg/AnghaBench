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

__attribute__((used)) static inline void wdt_timer_conf(unsigned char conf)
{
	/* -- Watchdog timer configuration --
	 * Bit 0   Joystick enable: 0* = No Reset, 1 = Reset WDT upon
	 *							Gameport I/O
	 * Bit 1   Keyboard enable: 0* = No Reset, 1 = Reset WDT upon KBD Intr.
	 * Bit 2   Mouse enable: 0* = No Reset, 1 = Reset WDT upon Mouse Intr
	 * Bit 3   Reset the timer
	 *         (Wrong in SMsC documentation? Given as: PowerLED Timout
	 *							Enabled)
	 * Bit 4-7 WDT Interrupt Mapping: (0000* = Disabled,
	 *            0001=IRQ1, 0010=(Invalid), 0011=IRQ3 to 1111=IRQ15)
	 */
	write_io_cr(0xF3, conf);
}