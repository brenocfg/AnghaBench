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
struct usb_stv {int removed; int /*<<< orphan*/  user; int /*<<< orphan*/ * vdev; } ;
struct usb_interface {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  stv680_remove_sysfs_files (int /*<<< orphan*/ *) ; 
 struct usb_stv* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_stv680_remove_disconnected (struct usb_stv*) ; 
 int /*<<< orphan*/  video_unregister_device (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void stv680_disconnect (struct usb_interface *intf)
{
	struct usb_stv *stv680 = usb_get_intfdata (intf);

	usb_set_intfdata (intf, NULL);

	if (stv680) {
		/* We don't want people trying to open up the device */
		if (stv680->vdev) {
			stv680_remove_sysfs_files(stv680->vdev);
			video_unregister_device(stv680->vdev);
			stv680->vdev = NULL;
		}
		if (!stv680->user) {
			usb_stv680_remove_disconnected (stv680);
		} else {
			stv680->removed = 1;
		}
	}
}