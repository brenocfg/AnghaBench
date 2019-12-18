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
struct scsi_device {scalar_t__ sdev_state; int /*<<< orphan*/  request_queue; } ;

/* Variables and functions */
 scalar_t__ SDEV_QUIESCE ; 
 int /*<<< orphan*/  SDEV_RUNNING ; 
 scalar_t__ scsi_device_set_state (struct scsi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_run_queue (int /*<<< orphan*/ ) ; 

void scsi_device_resume(struct scsi_device *sdev)
{
	/* check if the device state was mutated prior to resume, and if
	 * so assume the state is being managed elsewhere (for example
	 * device deleted during suspend)
	 */
	if (sdev->sdev_state != SDEV_QUIESCE ||
	    scsi_device_set_state(sdev, SDEV_RUNNING))
		return;
	scsi_run_queue(sdev->request_queue);
}