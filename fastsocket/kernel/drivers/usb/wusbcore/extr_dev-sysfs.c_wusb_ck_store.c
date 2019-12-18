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
struct wusbhc {int dummy; } ;
struct wusb_ckhdid {int /*<<< orphan*/ * data; } ;
struct usb_device {int /*<<< orphan*/  wusb_dev; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  ck ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  memset (struct wusb_ckhdid*,int /*<<< orphan*/ ,int) ; 
 int sscanf (char const*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct usb_device* to_usb_device (struct device*) ; 
 int wusb_dev_4way_handshake (struct wusbhc*,int /*<<< orphan*/ ,struct wusb_ckhdid*) ; 
 struct wusbhc* wusbhc_get_by_usb_dev (struct usb_device*) ; 
 int /*<<< orphan*/  wusbhc_put (struct wusbhc*) ; 

__attribute__((used)) static ssize_t wusb_ck_store(struct device *dev,
			     struct device_attribute *attr,
			     const char *buf, size_t size)
{
	int result;
	struct usb_device *usb_dev;
	struct wusbhc *wusbhc;
	struct wusb_ckhdid ck;

	result = sscanf(buf,
			"%02hhx %02hhx %02hhx %02hhx "
			"%02hhx %02hhx %02hhx %02hhx "
			"%02hhx %02hhx %02hhx %02hhx "
			"%02hhx %02hhx %02hhx %02hhx\n",
			&ck.data[0] , &ck.data[1],
			&ck.data[2] , &ck.data[3],
			&ck.data[4] , &ck.data[5],
			&ck.data[6] , &ck.data[7],
			&ck.data[8] , &ck.data[9],
			&ck.data[10], &ck.data[11],
			&ck.data[12], &ck.data[13],
			&ck.data[14], &ck.data[15]);
	if (result != 16)
		return -EINVAL;

	usb_dev = to_usb_device(dev);
	wusbhc = wusbhc_get_by_usb_dev(usb_dev);
	if (wusbhc == NULL)
		return -ENODEV;
	result = wusb_dev_4way_handshake(wusbhc, usb_dev->wusb_dev, &ck);
	memset(&ck, 0, sizeof(ck));
	wusbhc_put(wusbhc);
	return result < 0 ? result : size;
}