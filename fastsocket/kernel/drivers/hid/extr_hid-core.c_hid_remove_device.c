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
struct hid_device {int status; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int HID_STAT_ADDED ; 
 int /*<<< orphan*/  device_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hid_debug_unregister (struct hid_device*) ; 

__attribute__((used)) static void hid_remove_device(struct hid_device *hdev)
{
	if (hdev->status & HID_STAT_ADDED) {
		device_del(&hdev->dev);
		hid_debug_unregister(hdev);
		hdev->status &= ~HID_STAT_ADDED;
	}
}