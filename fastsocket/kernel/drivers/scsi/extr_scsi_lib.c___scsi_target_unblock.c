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
struct device {int dummy; } ;
typedef  enum scsi_device_state { ____Placeholder_scsi_device_state } scsi_device_state ;

/* Variables and functions */
 int /*<<< orphan*/  device_for_each_child (struct device*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_unblock ; 
 scalar_t__ scsi_is_target_device (struct device*) ; 
 int /*<<< orphan*/  starget_for_each_device (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  target_unblock ; 
 int /*<<< orphan*/  to_scsi_target (struct device*) ; 

void
__scsi_target_unblock(struct device *dev, enum scsi_device_state new_state)
{
	if (scsi_is_target_device(dev))
		starget_for_each_device(to_scsi_target(dev), &new_state,
					device_unblock);
	else
		device_for_each_child(dev, &new_state, target_unblock);
}