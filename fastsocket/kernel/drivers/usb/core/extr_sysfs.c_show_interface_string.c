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
struct usb_interface {TYPE_1__* cur_altsetting; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {char* string; } ;

/* Variables and functions */
 int /*<<< orphan*/  barrier () ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 struct usb_interface* to_usb_interface (struct device*) ; 

__attribute__((used)) static ssize_t show_interface_string(struct device *dev,
		struct device_attribute *attr, char *buf)
{
	struct usb_interface *intf;
	char *string;

	intf = to_usb_interface(dev);
	string = intf->cur_altsetting->string;
	barrier();		/* The altsetting might change! */

	if (!string)
		return 0;
	return sprintf(buf, "%s\n", string);
}