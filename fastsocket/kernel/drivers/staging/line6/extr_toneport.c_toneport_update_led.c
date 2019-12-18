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
struct usb_line6 {int /*<<< orphan*/  usbdev; } ;
struct usb_line6_toneport {struct usb_line6 line6; } ;
struct usb_interface {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  led_green ; 
 int led_red ; 
 struct usb_interface* to_usb_interface (struct device*) ; 
 int /*<<< orphan*/  toneport_send_cmd (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct usb_line6_toneport* usb_get_intfdata (struct usb_interface*) ; 

__attribute__((used)) static void toneport_update_led(struct device *dev)
{
	struct usb_interface *interface = to_usb_interface(dev);
	struct usb_line6_toneport *tp = usb_get_intfdata(interface);
	struct usb_line6 *line6;

	if (!tp)
		return;

	line6 = &tp->line6;
	if (line6)
		toneport_send_cmd(line6->usbdev, (led_red << 8) | 0x0002,
				  led_green);
}