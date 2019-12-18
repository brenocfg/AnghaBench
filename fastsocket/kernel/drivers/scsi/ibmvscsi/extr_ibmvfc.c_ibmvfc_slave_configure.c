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
struct scsi_device {scalar_t__ type; int allow_restart; int /*<<< orphan*/  queue_depth; scalar_t__ tagged_supported; struct Scsi_Host* host; } ;
struct Scsi_Host {int /*<<< orphan*/  host_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_SIMPLE_TAG ; 
 scalar_t__ TYPE_DISK ; 
 int /*<<< orphan*/  scsi_activate_tcq (struct scsi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_deactivate_tcq (struct scsi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_set_tag_type (struct scsi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static int ibmvfc_slave_configure(struct scsi_device *sdev)
{
	struct Scsi_Host *shost = sdev->host;
	unsigned long flags = 0;

	spin_lock_irqsave(shost->host_lock, flags);
	if (sdev->type == TYPE_DISK)
		sdev->allow_restart = 1;

	if (sdev->tagged_supported) {
		scsi_set_tag_type(sdev, MSG_SIMPLE_TAG);
		scsi_activate_tcq(sdev, sdev->queue_depth);
	} else
		scsi_deactivate_tcq(sdev, sdev->queue_depth);
	spin_unlock_irqrestore(shost->host_lock, flags);
	return 0;
}