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
struct scsi_device {int /*<<< orphan*/  request_queue; scalar_t__ device_busy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SDEV_QUIESCE ; 
 int /*<<< orphan*/  msleep_interruptible (int) ; 
 int scsi_device_set_state (struct scsi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_run_queue (int /*<<< orphan*/ ) ; 

int
scsi_device_quiesce(struct scsi_device *sdev)
{
	int err = scsi_device_set_state(sdev, SDEV_QUIESCE);
	if (err)
		return err;

	scsi_run_queue(sdev->request_queue);
	while (sdev->device_busy) {
		msleep_interruptible(200);
		scsi_run_queue(sdev->request_queue);
	}
	return 0;
}