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
struct usb_hcd {int dummy; } ;
struct hc_driver {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct usb_hcd* usb_create_shared_hcd (struct hc_driver const*,struct device*,char const*,int /*<<< orphan*/ *) ; 

struct usb_hcd *usb_create_hcd(const struct hc_driver *driver,
		struct device *dev, const char *bus_name)
{
	return usb_create_shared_hcd(driver, dev, bus_name, NULL);
}