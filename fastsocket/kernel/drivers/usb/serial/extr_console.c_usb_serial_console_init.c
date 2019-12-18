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
 int /*<<< orphan*/  dbg (char*) ; 
 int debug ; 
 int /*<<< orphan*/  register_console (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usbcons ; 

void usb_serial_console_init(int serial_debug, int minor)
{
	debug = serial_debug;

	if (minor == 0) {
		/*
		 * Call register_console() if this is the first device plugged
		 * in.  If we call it earlier, then the callback to
		 * console_setup() will fail, as there is not a device seen by
		 * the USB subsystem yet.
		 */
		/*
		 * Register console.
		 * NOTES:
		 * console_setup() is called (back) immediately (from
		 * register_console). console_write() is called immediately
		 * from register_console iff CON_PRINTBUFFER is set in flags.
		 */
		dbg("registering the USB serial console.");
		register_console(&usbcons);
	}
}