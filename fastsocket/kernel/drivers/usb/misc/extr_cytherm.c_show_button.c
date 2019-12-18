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
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUTTON ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  READ_RAM ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  kfree (unsigned char*) ; 
 unsigned char* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*) ; 
 struct usb_interface* to_usb_interface (struct device*) ; 
 struct usb_cytherm* usb_get_intfdata (struct usb_interface*) ; 
 int vendor_command (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,int) ; 

__attribute__((used)) static ssize_t show_button(struct device *dev, struct device_attribute *attr, char *buf)
{

	struct usb_interface *intf = to_usb_interface(dev);
	struct usb_cytherm *cytherm = usb_get_intfdata(intf);

	int retval;
	unsigned char *buffer;

	buffer = kmalloc(8, GFP_KERNEL);
	if (!buffer) {
		dev_err(&cytherm->udev->dev, "out of memory\n");
		return 0;
	}

	/* check button */
	retval = vendor_command(cytherm->udev, READ_RAM, BUTTON, 0, buffer, 8);
	if (retval)
		dev_dbg(&cytherm->udev->dev, "retval = %d\n", retval);
   
	retval = buffer[1];

	kfree(buffer);

	if (retval)
		return sprintf(buf, "1");
	else
		return sprintf(buf, "0");
}