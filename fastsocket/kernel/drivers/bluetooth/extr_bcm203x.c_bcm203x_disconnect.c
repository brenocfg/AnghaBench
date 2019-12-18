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
struct usb_interface {int dummy; } ;
struct bcm203x_data {struct bcm203x_data* buffer; struct bcm203x_data* fw_data; int /*<<< orphan*/  urb; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct usb_interface*) ; 
 int /*<<< orphan*/  kfree (struct bcm203x_data*) ; 
 int /*<<< orphan*/  usb_free_urb (int /*<<< orphan*/ ) ; 
 struct bcm203x_data* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bcm203x_disconnect(struct usb_interface *intf)
{
	struct bcm203x_data *data = usb_get_intfdata(intf);

	BT_DBG("intf %p", intf);

	usb_kill_urb(data->urb);

	usb_set_intfdata(intf, NULL);

	usb_free_urb(data->urb);
	kfree(data->fw_data);
	kfree(data->buffer);
	kfree(data);
}