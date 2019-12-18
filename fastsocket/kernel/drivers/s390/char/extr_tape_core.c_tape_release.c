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
struct tape_device {scalar_t__ tape_state; int /*<<< orphan*/  cdev; TYPE_1__* discipline; } ;
struct TYPE_2__ {int /*<<< orphan*/  owner; } ;

/* Variables and functions */
 scalar_t__ TS_IN_USE ; 
 int /*<<< orphan*/  TS_UNUSED ; 
 int /*<<< orphan*/  get_ccwdev_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tape_state_set (struct tape_device*,int /*<<< orphan*/ ) ; 

int
tape_release(struct tape_device *device)
{
	spin_lock_irq(get_ccwdev_lock(device->cdev));
	if (device->tape_state == TS_IN_USE)
		tape_state_set(device, TS_UNUSED);
	module_put(device->discipline->owner);
	spin_unlock_irq(get_ccwdev_lock(device->cdev));
	return 0;
}