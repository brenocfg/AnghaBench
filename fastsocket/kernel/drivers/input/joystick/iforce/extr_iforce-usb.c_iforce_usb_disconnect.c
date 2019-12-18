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
struct iforce {int /*<<< orphan*/  dev; int /*<<< orphan*/ * usbdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  iforce_delete_device (struct iforce*) ; 
 int /*<<< orphan*/  input_unregister_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct iforce*) ; 
 struct iforce* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void iforce_usb_disconnect(struct usb_interface *intf)
{
	struct iforce *iforce = usb_get_intfdata(intf);
	int open = 0; /* FIXME! iforce->dev.handle->open; */

	usb_set_intfdata(intf, NULL);
	if (iforce) {
		iforce->usbdev = NULL;
		input_unregister_device(iforce->dev);

		if (!open) {
			iforce_delete_device(iforce);
			kfree(iforce);
		}
	}
}