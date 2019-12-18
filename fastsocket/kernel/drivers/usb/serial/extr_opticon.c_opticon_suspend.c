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
struct usb_serial {int dummy; } ;
struct usb_interface {int dummy; } ;
struct opticon_private {int /*<<< orphan*/  bulk_read_urb; } ;
typedef  int /*<<< orphan*/  pm_message_t ;

/* Variables and functions */
 struct usb_serial* usb_get_intfdata (struct usb_interface*) ; 
 struct opticon_private* usb_get_serial_data (struct usb_serial*) ; 
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int opticon_suspend(struct usb_interface *intf, pm_message_t message)
{
	struct usb_serial *serial = usb_get_intfdata(intf);
	struct opticon_private *priv = usb_get_serial_data(serial);

	usb_kill_urb(priv->bulk_read_urb);
	return 0;
}