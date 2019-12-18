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

/* Variables and functions */
 int /*<<< orphan*/  device_block ; 
 int /*<<< orphan*/  device_for_each_child (struct device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ scsi_is_target_device (struct device*) ; 
 int /*<<< orphan*/  starget_for_each_device (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  target_block ; 
 int /*<<< orphan*/  to_scsi_target (struct device*) ; 

void
scsi_target_block(struct device *dev)
{
	if (scsi_is_target_device(dev))
		starget_for_each_device(to_scsi_target(dev), NULL,
					device_block);
	else
		device_for_each_child(dev, NULL, target_block);
}