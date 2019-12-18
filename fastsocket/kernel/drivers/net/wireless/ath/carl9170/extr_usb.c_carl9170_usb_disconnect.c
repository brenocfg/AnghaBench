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
struct usb_device {int dummy; } ;
struct ar9170 {int /*<<< orphan*/  fw_load_wait; struct usb_device* udev; } ;

/* Variables and functions */
 scalar_t__ IS_INITIALIZED (struct ar9170*) ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  carl9170_free (struct ar9170*) ; 
 int /*<<< orphan*/  carl9170_reboot (struct ar9170*) ; 
 int /*<<< orphan*/  carl9170_release_firmware (struct ar9170*) ; 
 int /*<<< orphan*/  carl9170_unregister (struct ar9170*) ; 
 int /*<<< orphan*/  carl9170_usb_cancel_urbs (struct ar9170*) ; 
 int /*<<< orphan*/  carl9170_usb_stop (struct ar9170*) ; 
 struct ar9170* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_put_dev (struct usb_device*) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void carl9170_usb_disconnect(struct usb_interface *intf)
{
	struct ar9170 *ar = usb_get_intfdata(intf);
	struct usb_device *udev;

	if (WARN_ON(!ar))
		return;

	udev = ar->udev;
	wait_for_completion(&ar->fw_load_wait);

	if (IS_INITIALIZED(ar)) {
		carl9170_reboot(ar);
		carl9170_usb_stop(ar);
	}

	carl9170_usb_cancel_urbs(ar);
	carl9170_unregister(ar);

	usb_set_intfdata(intf, NULL);

	carl9170_release_firmware(ar);
	carl9170_free(ar);
	usb_put_dev(udev);
}