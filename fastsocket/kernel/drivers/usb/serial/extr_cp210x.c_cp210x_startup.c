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
struct usb_serial {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  usb_reset_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cp210x_startup(struct usb_serial *serial)
{
	/* cp210x buffers behave strangely unless device is reset */
	usb_reset_device(serial->dev);
	return 0;
}