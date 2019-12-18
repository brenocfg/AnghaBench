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
struct swoc_info {int rev; int LinuxSKU; int LinuxVer; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 scalar_t__ TRU_FORCE_MS ; 
 int /*<<< orphan*/  US_DEBUGP (char*) ; 
 int /*<<< orphan*/  debug_swoc (struct swoc_info*) ; 
 struct usb_device* interface_to_usbdev (struct usb_interface*) ; 
 int /*<<< orphan*/  kfree (struct swoc_info*) ; 
 struct swoc_info* kmalloc (int,int /*<<< orphan*/ ) ; 
 int sierra_get_swoc_info (struct usb_device*,struct swoc_info*) ; 
 int snprintf (char*,int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ swi_tru_install ; 
 struct usb_interface* to_usb_interface (struct device*) ; 

__attribute__((used)) static ssize_t show_truinst(struct device *dev, struct device_attribute *attr,
			char *buf)
{
	struct swoc_info *swocInfo;
	struct usb_interface *intf = to_usb_interface(dev);
	struct usb_device *udev = interface_to_usbdev(intf);
	int result;
	if (swi_tru_install == TRU_FORCE_MS) {
		result = snprintf(buf, PAGE_SIZE, "Forced Mass Storage\n");
	} else {
		swocInfo = kmalloc(sizeof(struct swoc_info), GFP_KERNEL);
		if (!swocInfo) {
			US_DEBUGP("SWIMS: Allocation failure\n");
			snprintf(buf, PAGE_SIZE, "Error\n");
			return -ENOMEM;
		}
		result = sierra_get_swoc_info(udev, swocInfo);
		if (result < 0) {
			US_DEBUGP("SWIMS: failed SWoC query\n");
			kfree(swocInfo);
			snprintf(buf, PAGE_SIZE, "Error\n");
			return -EIO;
		}
		debug_swoc(swocInfo);
		result = snprintf(buf, PAGE_SIZE,
			"REV=%02d SKU=%04X VER=%04X\n",
			swocInfo->rev,
			swocInfo->LinuxSKU,
			swocInfo->LinuxVer);
		kfree(swocInfo);
	}
	return result;
}