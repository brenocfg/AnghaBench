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
struct usbatm_data {struct atm_dev* atm_dev; } ;
struct usb_interface {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct atm_dev {int /*<<< orphan*/  esi; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct usb_interface* to_usb_interface (struct device*) ; 
 struct usbatm_data* usb_get_intfdata (struct usb_interface*) ; 

__attribute__((used)) static ssize_t cxacru_sysfs_show_mac_address(struct device *dev,
	struct device_attribute *attr, char *buf)
{
	struct usb_interface *intf = to_usb_interface(dev);
	struct usbatm_data *usbatm_instance = usb_get_intfdata(intf);
	struct atm_dev *atm_dev = usbatm_instance->atm_dev;

	return snprintf(buf, PAGE_SIZE, "%pM\n", atm_dev->esi);
}