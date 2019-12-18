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
struct scsi_device {int /*<<< orphan*/  sdev_gendev; struct request_queue* request_queue; } ;
struct scsi_cmnd {struct scsi_device* device; } ;
struct request_queue {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scsi_put_command (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  scsi_run_queue (struct request_queue*) ; 

void scsi_next_command(struct scsi_cmnd *cmd)
{
	struct scsi_device *sdev = cmd->device;
	struct request_queue *q = sdev->request_queue;

	/* need to hold a reference on the device before we let go of the cmd */
	get_device(&sdev->sdev_gendev);

	scsi_put_command(cmd);
	scsi_run_queue(q);

	/* ok to remove device now */
	put_device(&sdev->sdev_gendev);
}