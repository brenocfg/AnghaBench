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
struct usbhid_device {int /*<<< orphan*/  reset_work; int /*<<< orphan*/  restart_work; int /*<<< orphan*/  io_retry; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hid_cancel_delayed_stuff(struct usbhid_device *usbhid)
{
	del_timer_sync(&usbhid->io_retry);
	cancel_work_sync(&usbhid->restart_work);
	cancel_work_sync(&usbhid->reset_work);
}