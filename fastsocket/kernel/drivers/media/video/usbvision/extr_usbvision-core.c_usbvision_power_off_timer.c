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
struct usb_usbvision {int /*<<< orphan*/  power_off_work; int /*<<< orphan*/  power_off_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_FUNC ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PDEBUG (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  call_usbvision_power_off ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void usbvision_power_off_timer(unsigned long data)
{
	struct usb_usbvision *usbvision = (void *)data;

	PDEBUG(DBG_FUNC, "");
	del_timer(&usbvision->power_off_timer);
	INIT_WORK(&usbvision->power_off_work, call_usbvision_power_off);
	(void) schedule_work(&usbvision->power_off_work);
}