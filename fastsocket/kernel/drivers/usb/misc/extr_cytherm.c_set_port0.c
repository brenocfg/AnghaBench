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
struct usb_cytherm {TYPE_1__* udev; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  WRITE_PORT ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  kfree (unsigned char*) ; 
 unsigned char* kmalloc (int,int /*<<< orphan*/ ) ; 
 int simple_strtoul (char const*,int /*<<< orphan*/ *,int) ; 
 struct usb_interface* to_usb_interface (struct device*) ; 
 struct usb_cytherm* usb_get_intfdata (struct usb_interface*) ; 
 int vendor_command (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,unsigned char*,int) ; 

__attribute__((used)) static ssize_t set_port0(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
{
	struct usb_interface *intf = to_usb_interface(dev);
	struct usb_cytherm *cytherm = usb_get_intfdata(intf);

	unsigned char *buffer;
	int retval;
	int tmp;
   
	buffer = kmalloc(8, GFP_KERNEL);
	if (!buffer) {
		dev_err(&cytherm->udev->dev, "out of memory\n");
		return 0;
	}

	tmp = simple_strtoul(buf, NULL, 10);
   
	if (tmp > 0xFF)
		tmp = 0xFF;
	else if (tmp < 0)
		tmp = 0;
   
	retval = vendor_command(cytherm->udev, WRITE_PORT, 0,
				tmp, buffer, 8);
	if (retval)
		dev_dbg(&cytherm->udev->dev, "retval = %d\n", retval);

	kfree(buffer);

	return count;
}