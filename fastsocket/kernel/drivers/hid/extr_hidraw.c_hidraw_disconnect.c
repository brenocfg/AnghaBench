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
struct hidraw {size_t minor; int /*<<< orphan*/  wait; scalar_t__ open; scalar_t__ exist; } ;
struct hid_device {TYPE_1__* ll_driver; struct hidraw* hidraw; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* close ) (struct hid_device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  MKDEV (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  device_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hidraw_class ; 
 int /*<<< orphan*/  hidraw_major ; 
 int /*<<< orphan*/ ** hidraw_table ; 
 int /*<<< orphan*/  kfree (struct hidraw*) ; 
 int /*<<< orphan*/  minors_lock ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct hid_device*) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

void hidraw_disconnect(struct hid_device *hid)
{
	struct hidraw *hidraw = hid->hidraw;

	mutex_lock(&minors_lock);
	hidraw->exist = 0;

	device_destroy(hidraw_class, MKDEV(hidraw_major, hidraw->minor));

	hidraw_table[hidraw->minor] = NULL;

	if (hidraw->open) {
		hid->ll_driver->close(hid);
		wake_up_interruptible(&hidraw->wait);
	} else {
		kfree(hidraw);
	}
	mutex_unlock(&minors_lock);
}