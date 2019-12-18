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
struct scsi_device {scalar_t__ device_busy; scalar_t__ queue_depth; scalar_t__ device_blocked; } ;

/* Variables and functions */

__attribute__((used)) static inline int scsi_device_is_busy(struct scsi_device *sdev)
{
	if (sdev->device_busy >= sdev->queue_depth || sdev->device_blocked)
		return 1;

	return 0;
}