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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct cbaf {int /*<<< orphan*/  cdid; } ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int /*<<< orphan*/  pr_cdid ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int WUSB_CKHDID_STRSIZE ; 
 int /*<<< orphan*/  ckhdid_printf (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scnprintf (char*,int /*<<< orphan*/ ,char*,char*) ; 
 struct usb_interface* to_usb_interface (struct device*) ; 
 struct cbaf* usb_get_intfdata (struct usb_interface*) ; 

__attribute__((used)) static ssize_t cbaf_wusb_cdid_show(struct device *dev,
				   struct device_attribute *attr, char *buf)
{
	struct usb_interface *iface = to_usb_interface(dev);
	struct cbaf *cbaf = usb_get_intfdata(iface);
	char pr_cdid[WUSB_CKHDID_STRSIZE];

	ckhdid_printf(pr_cdid, sizeof(pr_cdid), &cbaf->cdid);
	return scnprintf(buf, PAGE_SIZE, "%s\n", pr_cdid);
}