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
typedef  int u16 ;
struct TYPE_2__ {int /*<<< orphan*/  bcdUSB; } ;
struct usb_device {TYPE_1__ descriptor; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,int) ; 
 struct usb_device* to_usb_device (struct device*) ; 

__attribute__((used)) static ssize_t
show_version(struct device *dev, struct device_attribute *attr, char *buf)
{
	struct usb_device *udev;
	u16 bcdUSB;

	udev = to_usb_device(dev);
	bcdUSB = le16_to_cpu(udev->descriptor.bcdUSB);
	return sprintf(buf, "%2x.%02x\n", bcdUSB >> 8, bcdUSB & 0xff);
}