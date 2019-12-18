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
struct scsi_target {int /*<<< orphan*/  target_busy; } ;
struct scsi_device {TYPE_1__* request_queue; int /*<<< orphan*/  device_busy; struct Scsi_Host* host; } ;
struct Scsi_Host {int /*<<< orphan*/  host_lock; scalar_t__ host_eh_scheduled; scalar_t__ host_failed; int /*<<< orphan*/  host_busy; } ;
struct TYPE_2__ {int /*<<< orphan*/  queue_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  scsi_eh_wakeup (struct Scsi_Host*) ; 
 scalar_t__ scsi_host_in_recovery (struct Scsi_Host*) ; 
 struct scsi_target* scsi_target (struct scsi_device*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 scalar_t__ unlikely (int) ; 

void scsi_device_unbusy(struct scsi_device *sdev)
{
	struct Scsi_Host *shost = sdev->host;
	struct scsi_target *starget = scsi_target(sdev);
	unsigned long flags;

	spin_lock_irqsave(shost->host_lock, flags);
	shost->host_busy--;
	starget->target_busy--;
	if (unlikely(scsi_host_in_recovery(shost) &&
		     (shost->host_failed || shost->host_eh_scheduled)))
		scsi_eh_wakeup(shost);
	spin_unlock(shost->host_lock);
	spin_lock(sdev->request_queue->queue_lock);
	sdev->device_busy--;
	spin_unlock_irqrestore(sdev->request_queue->queue_lock, flags);
}