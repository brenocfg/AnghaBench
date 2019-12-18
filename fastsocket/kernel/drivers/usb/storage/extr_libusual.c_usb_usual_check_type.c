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
struct usb_device_id {int /*<<< orphan*/  driver_info; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int USB_US_TYPE (int /*<<< orphan*/ ) ; 
 int USB_US_TYPE_NONE ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usu_bias ; 

int usb_usual_check_type(const struct usb_device_id *id, int caller_type)
{
	int id_type = USB_US_TYPE(id->driver_info);

	if (caller_type <= 0 || caller_type >= 3)
		return -EINVAL;

	/* Drivers grab fixed assignment devices */
	if (id_type == caller_type)
		return 0;
	/* Drivers grab devices biased to them */
	if (id_type == USB_US_TYPE_NONE && caller_type == atomic_read(&usu_bias))
		return 0;
	return -ENODEV;
}