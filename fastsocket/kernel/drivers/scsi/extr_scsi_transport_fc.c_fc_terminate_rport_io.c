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
struct fc_rport {int /*<<< orphan*/  dev; } ;
struct fc_internal {TYPE_1__* f; } ;
struct Scsi_Host {int /*<<< orphan*/  transportt; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* terminate_rport_io ) (struct fc_rport*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  SDEV_TRANSPORT_OFFLINE ; 
 int /*<<< orphan*/  __scsi_target_unblock (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct Scsi_Host* rport_to_shost (struct fc_rport*) ; 
 int /*<<< orphan*/  stub1 (struct fc_rport*) ; 
 struct fc_internal* to_fc_internal (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fc_terminate_rport_io(struct fc_rport *rport)
{
	struct Scsi_Host *shost = rport_to_shost(rport);
	struct fc_internal *i = to_fc_internal(shost->transportt);

	/* Involve the LLDD if possible to terminate all io on the rport. */
	if (i->f->terminate_rport_io)
		i->f->terminate_rport_io(rport);

	/*
	 * Must unblock to flush queued IO. scsi-ml will fail incoming reqs.
	 */
	__scsi_target_unblock(&rport->dev, SDEV_TRANSPORT_OFFLINE);
}