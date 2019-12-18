#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct zfcp_unit {TYPE_2__* port; int /*<<< orphan*/  status; } ;
struct zfcp_adapter {int /*<<< orphan*/  dbf; } ;
struct scsi_cmnd {int result; void (* scsi_done ) (struct scsi_cmnd*) ;TYPE_3__* device; int /*<<< orphan*/ * host_scribble; } ;
struct fc_rport {int dummy; } ;
struct TYPE_6__ {struct zfcp_unit* hostdata; TYPE_1__* host; } ;
struct TYPE_5__ {int /*<<< orphan*/  status; struct zfcp_adapter* adapter; } ;
struct TYPE_4__ {scalar_t__* hostdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  DID_ERROR ; 
 int /*<<< orphan*/  DID_IMM_RETRY ; 
 int /*<<< orphan*/  DID_NO_CONNECT ; 
 int EBUSY ; 
 int SCSI_MLQUEUE_DEVICE_BUSY ; 
 int SCSI_MLQUEUE_HOST_BUSY ; 
 int ZFCP_STATUS_COMMON_ERP_FAILED ; 
 int ZFCP_STATUS_COMMON_UNBLOCKED ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int fc_remote_port_chkready (struct fc_rport*) ; 
 int /*<<< orphan*/  scsi_target (TYPE_3__*) ; 
 struct fc_rport* starget_to_rport (int /*<<< orphan*/ ) ; 
 void stub1 (struct scsi_cmnd*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  zfcp_dbf_scsi_result (char*,int,int /*<<< orphan*/ ,struct scsi_cmnd*,int /*<<< orphan*/ *) ; 
 int zfcp_fsf_send_fcp_command_task (struct zfcp_unit*,struct scsi_cmnd*) ; 
 int /*<<< orphan*/  zfcp_scsi_command_fail (struct scsi_cmnd*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int zfcp_scsi_queuecommand(struct scsi_cmnd *scpnt,
				  void (*done) (struct scsi_cmnd *))
{
	struct zfcp_unit *unit;
	struct zfcp_adapter *adapter;
	int    status, scsi_result, ret;
	struct fc_rport *rport = starget_to_rport(scsi_target(scpnt->device));

	/* reset the status for this request */
	scpnt->result = 0;
	scpnt->host_scribble = NULL;
	scpnt->scsi_done = done;

	/*
	 * figure out adapter and target device
	 * (stored there by zfcp_scsi_slave_alloc)
	 */
	adapter = (struct zfcp_adapter *) scpnt->device->host->hostdata[0];
	unit = scpnt->device->hostdata;

	BUG_ON(!adapter || (adapter != unit->port->adapter));
	BUG_ON(!scpnt->scsi_done);

	if (unlikely(!unit)) {
		zfcp_scsi_command_fail(scpnt, DID_NO_CONNECT);
		return 0;
	}

	scsi_result = fc_remote_port_chkready(rport);
	if (unlikely(scsi_result)) {
		scpnt->result = scsi_result;
		zfcp_dbf_scsi_result("fail", 4, adapter->dbf, scpnt, NULL);
		scpnt->scsi_done(scpnt);
		return 0;
	}

	status = atomic_read(&unit->status);
	if (unlikely(status & ZFCP_STATUS_COMMON_ERP_FAILED) &&
		     !(atomic_read(&unit->port->status) &
		       ZFCP_STATUS_COMMON_ERP_FAILED)) {
		/* only unit access denied, but port is good
		 * not covered by FC transport, have to fail here */
		zfcp_scsi_command_fail(scpnt, DID_ERROR);
		return 0;
	}

	if (unlikely(!(status & ZFCP_STATUS_COMMON_UNBLOCKED))) {
		/* This could be either
		 * open unit pending: this is temporary, will result in
		 * 	open unit or ERP_FAILED, so retry command
		 * call to rport_delete pending: mimic retry from
		 * 	fc_remote_port_chkready until rport is BLOCKED
		 */
		zfcp_scsi_command_fail(scpnt, DID_IMM_RETRY);
		return 0;
	}

	ret = zfcp_fsf_send_fcp_command_task(unit, scpnt);
	if (unlikely(ret == -EBUSY))
		return SCSI_MLQUEUE_DEVICE_BUSY;
	else if (unlikely(ret < 0))
		return SCSI_MLQUEUE_HOST_BUSY;

	return ret;
}