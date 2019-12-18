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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 int /*<<< orphan*/  to_usb_device (struct device*) ; 
 scalar_t__ usb_device_supports_ltm (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t
show_ltm_capable(struct device *dev, struct device_attribute *attr, char *buf)
{
	if (usb_device_supports_ltm(to_usb_device(dev)))
		return sprintf(buf, "%s\n", "yes");
	return sprintf(buf, "%s\n", "no");
}