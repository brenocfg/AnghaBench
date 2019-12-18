#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* port; } ;
struct TYPE_3__ {scalar_t__ console; } ;

/* Variables and functions */
 int /*<<< orphan*/  unregister_console (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usbcons ; 
 TYPE_2__ usbcons_info ; 

void usb_serial_console_exit(void)
{
	if (usbcons_info.port) {
		unregister_console(&usbcons);
		usbcons_info.port->console = 0;
		usbcons_info.port = NULL;
	}
}