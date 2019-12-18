#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int mbox_int; scalar_t__ mbox_busy; } ;
struct qla_hw_data {int /*<<< orphan*/  mbx_intr_comp; int /*<<< orphan*/  mbx_cmd_flags; TYPE_1__ flags; } ;
struct TYPE_6__ {struct qla_hw_data* hw; } ;
typedef  TYPE_2__ scsi_qla_host_t ;

/* Variables and functions */
 int /*<<< orphan*/  MBX_INTR_WAIT ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ql_log (int /*<<< orphan*/ ,TYPE_2__*,int,char*) ; 
 int /*<<< orphan*/  ql_log_warn ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void qla82xx_clear_pending_mbx(scsi_qla_host_t *vha)
{
	struct qla_hw_data *ha = vha->hw;

	if (ha->flags.mbox_busy) {
		ha->flags.mbox_int = 1;
		ha->flags.mbox_busy = 0;
		ql_log(ql_log_warn, vha, 0x6010,
		    "Doing premature completion of mbx command.\n");
		if (test_and_clear_bit(MBX_INTR_WAIT, &ha->mbx_cmd_flags))
			complete(&ha->mbx_intr_comp);
	}
}