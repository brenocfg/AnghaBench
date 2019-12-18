#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct scsi_cmnd {TYPE_2__* device; TYPE_1__* request; } ;
typedef  struct fc_port fc_port ;
struct TYPE_10__ {int /*<<< orphan*/  host_no; } ;
typedef  TYPE_3__ scsi_qla_host_t ;
typedef  struct fc_port fc_port_t ;
typedef  enum nexus_wait_type { ____Placeholder_nexus_wait_type } nexus_wait_type ;
struct TYPE_9__ {unsigned int lun; int /*<<< orphan*/  id; scalar_t__ hostdata; int /*<<< orphan*/  host; } ;
struct TYPE_8__ {int cpu; } ;

/* Variables and functions */
 int FAILED ; 
 int QLA_SUCCESS ; 
 int SUCCESS ; 
 int fc_block_scsi_eh (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  ql_log (int /*<<< orphan*/ ,TYPE_3__*,int,char*,...) ; 
 int /*<<< orphan*/  ql_log_info ; 
 int /*<<< orphan*/  ql_log_warn ; 
 int qla2x00_eh_wait_for_pending_commands (TYPE_3__*,int /*<<< orphan*/ ,unsigned int,int) ; 
 int qla2x00_wait_for_hba_online (TYPE_3__*) ; 
 int /*<<< orphan*/ * reset_errors ; 
 TYPE_3__* shost_priv (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
__qla2xxx_eh_generic_reset(char *name, enum nexus_wait_type type,
    struct scsi_cmnd *cmd, int (*do_reset)(struct fc_port *, unsigned int, int))
{
	scsi_qla_host_t *vha = shost_priv(cmd->device->host);
	fc_port_t *fcport = (struct fc_port *) cmd->device->hostdata;
	int err;

	if (!fcport) {
		return FAILED;
	}
	err = fc_block_scsi_eh(cmd);
	if (err != 0)
		return err;

	ql_log(ql_log_info, vha, 0x8009,
	    "%s RESET ISSUED nexus=%ld:%d:%d cmd=%p.\n", name, vha->host_no,
	    cmd->device->id, cmd->device->lun, cmd);

	err = 0;
	if (qla2x00_wait_for_hba_online(vha) != QLA_SUCCESS) {
		ql_log(ql_log_warn, vha, 0x800a,
		    "Wait for hba online failed for cmd=%p.\n", cmd);
		goto eh_reset_failed;
	}
	err = 2;
	if (do_reset(fcport, cmd->device->lun, cmd->request->cpu + 1)
		!= QLA_SUCCESS) {
		ql_log(ql_log_warn, vha, 0x800c,
		    "do_reset failed for cmd=%p.\n", cmd);
		goto eh_reset_failed;
	}
	err = 3;
	if (qla2x00_eh_wait_for_pending_commands(vha, cmd->device->id,
	    cmd->device->lun, type) != QLA_SUCCESS) {
		goto eh_reset_failed;
		ql_log(ql_log_warn, vha, 0x800d,
		    "wait for pending cmds failed for cmd=%p.\n", cmd);
	}
	ql_log(ql_log_info, vha, 0x800e,
	    "%s RESET SUCCEEDED nexus:%ld:%d:%d cmd=%p.\n", name,
	    vha->host_no, cmd->device->id, cmd->device->lun, cmd);

	return SUCCESS;

eh_reset_failed:
	ql_log(ql_log_info, vha, 0x800f,
	    "%s RESET FAILED: %s nexus=%ld:%d:%d cmd=%p.\n", name,
	    reset_errors[err], vha->host_no, cmd->device->id, cmd->device->lun,
	    cmd);
	return FAILED;
}