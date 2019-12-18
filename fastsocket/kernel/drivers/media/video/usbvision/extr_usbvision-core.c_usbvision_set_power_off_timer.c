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
struct usb_usbvision {int /*<<< orphan*/  power_off_timer; } ;

/* Variables and functions */
 scalar_t__ USBVISION_POWEROFF_TIME ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 

void usbvision_set_power_off_timer(struct usb_usbvision *usbvision)
{
	mod_timer(&usbvision->power_off_timer, jiffies + USBVISION_POWEROFF_TIME);
}