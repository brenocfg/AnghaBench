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
struct scsi_cmnd {TYPE_1__* device; } ;
struct fc_rport {scalar_t__ port_state; int flags; } ;
struct Scsi_Host {int /*<<< orphan*/  host_lock; } ;
struct TYPE_2__ {struct Scsi_Host* host; } ;

/* Variables and functions */
 int FAST_IO_FAIL ; 
 scalar_t__ FC_PORTSTATE_BLOCKED ; 
 int FC_RPORT_FAST_FAIL_TIMEDOUT ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  scsi_target (TYPE_1__*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 struct fc_rport* starget_to_rport (int /*<<< orphan*/ ) ; 

int fc_block_scsi_eh(struct scsi_cmnd *cmnd)
{
	struct Scsi_Host *shost = cmnd->device->host;
	struct fc_rport *rport = starget_to_rport(scsi_target(cmnd->device));
	unsigned long flags;

	spin_lock_irqsave(shost->host_lock, flags);
	while (rport->port_state == FC_PORTSTATE_BLOCKED &&
	       !(rport->flags & FC_RPORT_FAST_FAIL_TIMEDOUT)) {
		spin_unlock_irqrestore(shost->host_lock, flags);
		msleep(1000);
		spin_lock_irqsave(shost->host_lock, flags);
	}
	spin_unlock_irqrestore(shost->host_lock, flags);

	if (rport->flags & FC_RPORT_FAST_FAIL_TIMEDOUT)
		return FAST_IO_FAIL;

	return 0;
}