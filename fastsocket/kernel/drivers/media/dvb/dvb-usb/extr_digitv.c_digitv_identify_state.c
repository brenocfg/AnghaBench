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
struct TYPE_2__ {scalar_t__ iManufacturer; scalar_t__ iProduct; } ;
struct usb_device {TYPE_1__ descriptor; } ;
struct dvb_usb_device_properties {int dummy; } ;
struct dvb_usb_device_description {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int digitv_identify_state (struct usb_device *udev, struct
		dvb_usb_device_properties *props, struct dvb_usb_device_description **desc,
		int *cold)
{
	*cold = udev->descriptor.iManufacturer == 0 && udev->descriptor.iProduct == 0;
	return 0;
}