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
struct TYPE_2__ {long data; int /*<<< orphan*/  function; } ;
struct usb_usbvision {TYPE_1__ power_off_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  init_timer (TYPE_1__*) ; 
 int /*<<< orphan*/  usbvision_power_off_timer ; 

void usbvision_init_power_off_timer(struct usb_usbvision *usbvision)
{
	init_timer(&usbvision->power_off_timer);
	usbvision->power_off_timer.data = (long)usbvision;
	usbvision->power_off_timer.function = usbvision_power_off_timer;
}