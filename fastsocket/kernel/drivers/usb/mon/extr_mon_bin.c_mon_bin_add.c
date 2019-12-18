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
struct usb_bus {unsigned int busnum; int /*<<< orphan*/ * controller; } ;
struct mon_bus {struct device* classdev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct device*) ; 
 int /*<<< orphan*/  MAJOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MKDEV (int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int MON_BIN_MAX_MINOR ; 
 struct device* device_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,unsigned int) ; 
 int /*<<< orphan*/  mon_bin_class ; 
 int /*<<< orphan*/  mon_bin_dev0 ; 

int mon_bin_add(struct mon_bus *mbus, const struct usb_bus *ubus)
{
	struct device *dev;
	unsigned minor = ubus? ubus->busnum: 0;

	if (minor >= MON_BIN_MAX_MINOR)
		return 0;

	dev = device_create(mon_bin_class, ubus ? ubus->controller : NULL,
			    MKDEV(MAJOR(mon_bin_dev0), minor), NULL,
			    "usbmon%d", minor);
	if (IS_ERR(dev))
		return 0;

	mbus->classdev = dev;
	return 1;
}