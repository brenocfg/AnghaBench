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
typedef  int /*<<< orphan*/  u8 ;
struct wusbhc {int /*<<< orphan*/  mutex; } ;
struct wusb_dev {int /*<<< orphan*/  usb_dev; } ;
struct device {int dummy; } ;
struct usb_device {scalar_t__ wusb; int devnum; int /*<<< orphan*/  wusb_dev; int /*<<< orphan*/  portnum; struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  USB_STATE_UNAUTHENTICATED ; 
 struct wusb_dev* __wusb_dev_get_by_usb_dev (struct wusbhc*,struct usb_device*) ; 
 int /*<<< orphan*/  __wusbhc_dev_disconnect (struct wusbhc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_get_dev (struct usb_device*) ; 
 int /*<<< orphan*/  usb_set_device_state (struct usb_device*,int /*<<< orphan*/ ) ; 
 int wusb_dev_bos_add (struct usb_device*,struct wusb_dev*) ; 
 int /*<<< orphan*/  wusb_dev_bos_rm (struct wusb_dev*) ; 
 int /*<<< orphan*/  wusb_dev_get (struct wusb_dev*) ; 
 int /*<<< orphan*/  wusb_dev_put (struct wusb_dev*) ; 
 int wusb_dev_sec_add (struct wusbhc*,struct usb_device*,struct wusb_dev*) ; 
 int /*<<< orphan*/  wusb_dev_sec_rm (struct wusb_dev*) ; 
 int wusb_dev_sysfs_add (struct wusbhc*,struct usb_device*,struct wusb_dev*) ; 
 int /*<<< orphan*/  wusb_dev_sysfs_rm (struct wusb_dev*) ; 
 int /*<<< orphan*/  wusb_port_by_idx (struct wusbhc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wusb_port_no_to_idx (int /*<<< orphan*/ ) ; 
 struct wusbhc* wusbhc_get_by_usb_dev (struct usb_device*) ; 
 int /*<<< orphan*/  wusbhc_put (struct wusbhc*) ; 

__attribute__((used)) static void wusb_dev_add_ncb(struct usb_device *usb_dev)
{
	int result = 0;
	struct wusb_dev *wusb_dev;
	struct wusbhc *wusbhc;
	struct device *dev = &usb_dev->dev;
	u8 port_idx;

	if (usb_dev->wusb == 0 || usb_dev->devnum == 1)
		return;		/* skip non wusb and wusb RHs */

	usb_set_device_state(usb_dev, USB_STATE_UNAUTHENTICATED);

	wusbhc = wusbhc_get_by_usb_dev(usb_dev);
	if (wusbhc == NULL)
		goto error_nodev;
	mutex_lock(&wusbhc->mutex);
	wusb_dev = __wusb_dev_get_by_usb_dev(wusbhc, usb_dev);
	port_idx = wusb_port_no_to_idx(usb_dev->portnum);
	mutex_unlock(&wusbhc->mutex);
	if (wusb_dev == NULL)
		goto error_nodev;
	wusb_dev->usb_dev = usb_get_dev(usb_dev);
	usb_dev->wusb_dev = wusb_dev_get(wusb_dev);
	result = wusb_dev_sec_add(wusbhc, usb_dev, wusb_dev);
	if (result < 0) {
		dev_err(dev, "Cannot enable security: %d\n", result);
		goto error_sec_add;
	}
	/* Now query the device for it's BOS and attach it to wusb_dev */
	result = wusb_dev_bos_add(usb_dev, wusb_dev);
	if (result < 0) {
		dev_err(dev, "Cannot get BOS descriptors: %d\n", result);
		goto error_bos_add;
	}
	result = wusb_dev_sysfs_add(wusbhc, usb_dev, wusb_dev);
	if (result < 0)
		goto error_add_sysfs;
out:
	wusb_dev_put(wusb_dev);
	wusbhc_put(wusbhc);
error_nodev:
	return;

	wusb_dev_sysfs_rm(wusb_dev);
error_add_sysfs:
	wusb_dev_bos_rm(wusb_dev);
error_bos_add:
	wusb_dev_sec_rm(wusb_dev);
error_sec_add:
	mutex_lock(&wusbhc->mutex);
	__wusbhc_dev_disconnect(wusbhc, wusb_port_by_idx(wusbhc, port_idx));
	mutex_unlock(&wusbhc->mutex);
	goto out;
}