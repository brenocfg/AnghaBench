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
struct srp_target_port {int /*<<< orphan*/  scsi_host; } ;
struct srp_request {int /*<<< orphan*/  index; } ;
struct scsi_cmnd {int result; int /*<<< orphan*/  (* scsi_done ) (struct scsi_cmnd*) ;TYPE_1__* device; scalar_t__ host_scribble; } ;
struct TYPE_2__ {int /*<<< orphan*/  lun; int /*<<< orphan*/  host; } ;

/* Variables and functions */
 int DID_ABORT ; 
 int FAILED ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  SRP_TSK_ABORT_TASK ; 
 int SUCCESS ; 
 struct srp_target_port* host_to_target (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shost_printk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  srp_claim_req (struct srp_target_port*,struct srp_request*,struct scsi_cmnd*) ; 
 int /*<<< orphan*/  srp_free_req (struct srp_target_port*,struct srp_request*,struct scsi_cmnd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  srp_send_tsk_mgmt (struct srp_target_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct scsi_cmnd*) ; 

__attribute__((used)) static int srp_abort(struct scsi_cmnd *scmnd)
{
	struct srp_target_port *target = host_to_target(scmnd->device->host);
	struct srp_request *req = (struct srp_request *) scmnd->host_scribble;

	shost_printk(KERN_ERR, target->scsi_host, "SRP abort called\n");

	if (!req || !srp_claim_req(target, req, scmnd))
		return FAILED;
	srp_send_tsk_mgmt(target, req->index, scmnd->device->lun,
			  SRP_TSK_ABORT_TASK);
	srp_free_req(target, req, scmnd, 0);
	scmnd->result = DID_ABORT << 16;
	scmnd->scsi_done(scmnd);

	return SUCCESS;
}