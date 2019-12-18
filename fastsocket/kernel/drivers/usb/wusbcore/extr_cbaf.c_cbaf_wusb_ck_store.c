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
struct cbaf {TYPE_1__ ck; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 int cbaf_cc_upload (struct cbaf*) ; 
 int sscanf (char const*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct usb_interface* to_usb_interface (struct device*) ; 
 struct cbaf* usb_get_intfdata (struct usb_interface*) ; 

__attribute__((used)) static ssize_t cbaf_wusb_ck_store(struct device *dev,
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
			&cbaf->ck.data[0] , &cbaf->ck.data[1],
			&cbaf->ck.data[2] , &cbaf->ck.data[3],
			&cbaf->ck.data[4] , &cbaf->ck.data[5],
			&cbaf->ck.data[6] , &cbaf->ck.data[7],
			&cbaf->ck.data[8] , &cbaf->ck.data[9],
			&cbaf->ck.data[10], &cbaf->ck.data[11],
			&cbaf->ck.data[12], &cbaf->ck.data[13],
			&cbaf->ck.data[14], &cbaf->ck.data[15]);
	if (result != 16)
		return -EINVAL;

	result = cbaf_cc_upload(cbaf);
	if (result < 0)
		return result;

	return size;
}