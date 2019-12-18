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
struct wusbhc {int /*<<< orphan*/  mutex; } ;
struct wusb_dev {int dummy; } ;
struct usb_device {int dummy; } ;

/* Variables and functions */
 struct wusb_dev* __wusb_dev_get_by_usb_dev (struct wusbhc*,struct usb_device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct wusbhc* wusbhc_get_by_usb_dev (struct usb_device*) ; 
 int /*<<< orphan*/  wusbhc_put (struct wusbhc*) ; 

__attribute__((used)) static inline
struct wusb_dev *wusb_dev_get_by_usb_dev(struct usb_device *usb_dev)
{
	struct wusbhc *wusbhc;
	struct wusb_dev *wusb_dev;
	wusbhc = wusbhc_get_by_usb_dev(usb_dev);
	if (wusbhc == NULL)
		return NULL;
	mutex_lock(&wusbhc->mutex);
	wusb_dev = __wusb_dev_get_by_usb_dev(wusbhc, usb_dev);
	mutex_unlock(&wusbhc->mutex);
	wusbhc_put(wusbhc);
	return wusb_dev;
}