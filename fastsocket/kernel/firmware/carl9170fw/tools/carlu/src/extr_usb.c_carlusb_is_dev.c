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
struct libusb_device {int dummy; } ;
struct carlu {int /*<<< orphan*/  dev; } ;
typedef  struct libusb_device libusb_device ;

/* Variables and functions */
 scalar_t__ libusb_get_bus_number (struct libusb_device*) ; 
 struct libusb_device* libusb_get_device (int /*<<< orphan*/ ) ; 
 scalar_t__ libusb_get_device_address (struct libusb_device*) ; 

__attribute__((used)) static bool carlusb_is_dev(struct carlu *iter,
			       struct libusb_device *dev)
{
	libusb_device *list_dev;

	if (!iter->dev)
		return false;

	list_dev = libusb_get_device(iter->dev);

	if (libusb_get_bus_number(list_dev) == libusb_get_bus_number(dev) &&
	    libusb_get_device_address(list_dev) == libusb_get_device_address(dev))
		return true;

	return false;
}