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
struct TYPE_2__ {int /*<<< orphan*/  kobj; } ;
struct ib_device {scalar_t__ reg_state; TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ IB_DEV_UNINITIALIZED ; 
 scalar_t__ IB_DEV_UNREGISTERED ; 
 int /*<<< orphan*/  kfree (struct ib_device*) ; 
 int /*<<< orphan*/  kobject_put (int /*<<< orphan*/ *) ; 

void ib_dealloc_device(struct ib_device *device)
{
	if (device->reg_state == IB_DEV_UNINITIALIZED) {
		kfree(device);
		return;
	}

	BUG_ON(device->reg_state != IB_DEV_UNREGISTERED);

	kobject_put(&device->dev.kobj);
}