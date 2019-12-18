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
struct hso_device {scalar_t__ is_active; int /*<<< orphan*/  async_put_intf; TYPE_1__* usb; } ;
struct TYPE_2__ {scalar_t__ state; } ;

/* Variables and functions */
 int EAGAIN ; 
 scalar_t__ USB_STATE_SUSPENDED ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hso_put_activity(struct hso_device *hso_dev)
{
	if (hso_dev->usb->state != USB_STATE_SUSPENDED) {
		if (hso_dev->is_active) {
			hso_dev->is_active = 0;
			schedule_work(&hso_dev->async_put_intf);
			return -EAGAIN;
		}
	}
	hso_dev->is_active = 0;
	return 0;
}