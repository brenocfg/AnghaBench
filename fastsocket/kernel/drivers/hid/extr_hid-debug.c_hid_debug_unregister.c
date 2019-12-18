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
struct hid_device {int /*<<< orphan*/  debug_dir; int /*<<< orphan*/  debug_events; int /*<<< orphan*/  debug_rdesc; int /*<<< orphan*/  debug_wait; scalar_t__ debug; } ;

/* Variables and functions */
 int /*<<< orphan*/  debugfs_remove (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

void hid_debug_unregister(struct hid_device *hdev)
{
	hdev->debug = 0;
	wake_up_interruptible(&hdev->debug_wait);
	debugfs_remove(hdev->debug_rdesc);
	debugfs_remove(hdev->debug_events);
	debugfs_remove(hdev->debug_dir);
}