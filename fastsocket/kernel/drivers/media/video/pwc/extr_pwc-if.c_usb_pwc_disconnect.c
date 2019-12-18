#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct usb_interface {int dummy; } ;
struct pwc_device {int unplugged; int /*<<< orphan*/  modlock; scalar_t__ vopen; int /*<<< orphan*/  frameq; int /*<<< orphan*/  error_status; int /*<<< orphan*/ * udev; } ;
struct TYPE_2__ {struct pwc_device* pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  EPIPE ; 
 int MAX_DEV_HINTS ; 
 int /*<<< orphan*/  PWC_DEBUG_PROBE (char*) ; 
 int /*<<< orphan*/  PWC_ERROR (char*,...) ; 
 int /*<<< orphan*/  PWC_INFO (char*) ; 
 TYPE_1__* device_hint ; 
 int /*<<< orphan*/ * interface_to_usbdev (struct usb_interface*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pwc_cleanup (struct pwc_device*) ; 
 int /*<<< orphan*/  pwc_iso_stop (struct pwc_device*) ; 
 struct pwc_device* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void usb_pwc_disconnect(struct usb_interface *intf)
{
	struct pwc_device *pdev;
	int hint;

	pdev = usb_get_intfdata (intf);
	mutex_lock(&pdev->modlock);
	usb_set_intfdata (intf, NULL);
	if (pdev == NULL) {
		PWC_ERROR("pwc_disconnect() Called without private pointer.\n");
		goto disconnect_out;
	}
	if (pdev->udev == NULL) {
		PWC_ERROR("pwc_disconnect() already called for %p\n", pdev);
		goto disconnect_out;
	}
	if (pdev->udev != interface_to_usbdev(intf)) {
		PWC_ERROR("pwc_disconnect() Woops: pointer mismatch udev/pdev.\n");
		goto disconnect_out;
	}

	/* We got unplugged; this is signalled by an EPIPE error code */
	if (pdev->vopen) {
		PWC_INFO("Disconnected while webcam is in use!\n");
		pdev->error_status = EPIPE;
	}

	/* Alert waiting processes */
	wake_up_interruptible(&pdev->frameq);
	/* Wait until device is closed */
	if (pdev->vopen) {
		pdev->unplugged = 1;
		pwc_iso_stop(pdev);
	} else {
		/* Device is closed, so we can safely unregister it */
		PWC_DEBUG_PROBE("Unregistering video device in disconnect().\n");
		pwc_cleanup(pdev);

disconnect_out:
		/* search device_hint[] table if we occupy a slot, by any chance */
		for (hint = 0; hint < MAX_DEV_HINTS; hint++)
			if (device_hint[hint].pdev == pdev)
				device_hint[hint].pdev = NULL;
	}

	mutex_unlock(&pdev->modlock);
}