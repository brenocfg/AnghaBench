#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct resource {int dummy; } ;
struct TYPE_3__ {struct resource* resource; } ;

/* Variables and functions */
 int platform_device_register (TYPE_1__*) ; 
 TYPE_1__ realview_usb_device ; 

int realview_usb_register(struct resource *res)
{
	realview_usb_device.resource = res;
	return platform_device_register(&realview_usb_device);
}