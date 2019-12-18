#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct scsi_cmnd {TYPE_1__* device; } ;
struct TYPE_7__ {scalar_t__ eeh_busy; } ;
struct qla_hw_data {TYPE_2__ flags; int /*<<< orphan*/  pdev; } ;
struct TYPE_8__ {struct qla_hw_data* hw; } ;
typedef  TYPE_3__ scsi_qla_host_t ;
struct TYPE_6__ {int /*<<< orphan*/  host; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABORT_POLLING_PERIOD ; 
 unsigned long ABORT_WAIT_ITER ; 
 scalar_t__ CMD_SP (struct scsi_cmnd*) ; 
 int QLA_FUNCTION_FAILED ; 
 int QLA_SUCCESS ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_channel_offline (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ql_dbg (int /*<<< orphan*/ ,TYPE_3__*,int,char*) ; 
 int /*<<< orphan*/  ql_dbg_taskm ; 
 TYPE_3__* shost_priv (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
qla2x00_eh_wait_on_command(struct scsi_cmnd *cmd)
{
#define ABORT_POLLING_PERIOD	1000
#define ABORT_WAIT_ITER		((10 * 1000) / (ABORT_POLLING_PERIOD))
	unsigned long wait_iter = ABORT_WAIT_ITER;
	scsi_qla_host_t *vha = shost_priv(cmd->device->host);
	struct qla_hw_data *ha = vha->hw;
	int ret = QLA_SUCCESS;

	if (unlikely(pci_channel_offline(ha->pdev)) || ha->flags.eeh_busy) {
		ql_dbg(ql_dbg_taskm, vha, 0x8005,
		    "Return:eh_wait.\n");
		return ret;
	}

	while (CMD_SP(cmd) && wait_iter--) {
		msleep(ABORT_POLLING_PERIOD);
	}
	if (CMD_SP(cmd))
		ret = QLA_FUNCTION_FAILED;

	return ret;
}