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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * data; } ;
struct cbaf {TYPE_1__ chid; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 int cbaf_cdid_get (struct cbaf*) ; 
 int cbaf_send_host_info (struct cbaf*) ; 
 int sscanf (char const*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct usb_interface* to_usb_interface (struct device*) ; 
 struct cbaf* usb_get_intfdata (struct usb_interface*) ; 

__attribute__((used)) static ssize_t cbaf_wusb_chid_store(struct device *dev,
					 struct device_attribute *attr,
					 const char *buf, size_t size)
{
	ssize_t result;
	struct usb_interface *iface = to_usb_interface(dev);
	struct cbaf *cbaf = usb_get_intfdata(iface);

	result = sscanf(buf,
			"%02hhx %02hhx %02hhx %02hhx "
			"%02hhx %02hhx %02hhx %02hhx "
			"%02hhx %02hhx %02hhx %02hhx "
			"%02hhx %02hhx %02hhx %02hhx",
			&cbaf->chid.data[0] , &cbaf->chid.data[1],
			&cbaf->chid.data[2] , &cbaf->chid.data[3],
			&cbaf->chid.data[4] , &cbaf->chid.data[5],
			&cbaf->chid.data[6] , &cbaf->chid.data[7],
			&cbaf->chid.data[8] , &cbaf->chid.data[9],
			&cbaf->chid.data[10], &cbaf->chid.data[11],
			&cbaf->chid.data[12], &cbaf->chid.data[13],
			&cbaf->chid.data[14], &cbaf->chid.data[15]);

	if (result != 16)
		return -EINVAL;

	result = cbaf_send_host_info(cbaf);
	if (result < 0)
		return result;
	result = cbaf_cdid_get(cbaf);
	if (result < 0)
		return -result;
	return size;
}