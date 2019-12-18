#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint16_t ;
struct TYPE_15__ {scalar_t__ rsvd_1; int /*<<< orphan*/  domain; int /*<<< orphan*/  area; int /*<<< orphan*/  al_pa; } ;
struct TYPE_16__ {TYPE_3__ b; } ;
struct TYPE_17__ {TYPE_4__ d_id; int /*<<< orphan*/  port_name; } ;
typedef  TYPE_5__ sw_info_t ;
struct TYPE_13__ {int /*<<< orphan*/ * param; } ;
struct TYPE_14__ {int* gpn_data; TYPE_1__ cmd; } ;
struct sns_cmd_pkt {TYPE_2__ p; } ;
struct qla_hw_data {size_t max_fibre_devices; int /*<<< orphan*/  sns_cmd_dma; } ;
struct TYPE_18__ {struct qla_hw_data* hw; } ;
typedef  TYPE_6__ scsi_qla_host_t ;

/* Variables and functions */
 int /*<<< orphan*/  GPN_ID_CMD ; 
 int GPN_ID_SNS_CMD_SIZE ; 
 int /*<<< orphan*/  GPN_ID_SNS_DATA_SIZE ; 
 int /*<<< orphan*/  GPN_ID_SNS_SCMD_LEN ; 
 int QLA_FUNCTION_FAILED ; 
 int QLA_SUCCESS ; 
 int /*<<< orphan*/  WWN_SIZE ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ql_dbg (scalar_t__,TYPE_6__*,int,char*,...) ; 
 scalar_t__ ql_dbg_buffer ; 
 scalar_t__ ql_dbg_disc ; 
 int /*<<< orphan*/  ql_dump_buffer (scalar_t__,TYPE_6__*,int,int*,int) ; 
 struct sns_cmd_pkt* qla2x00_prep_sns_cmd (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int qla2x00_send_sns (TYPE_6__*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int
qla2x00_sns_gpn_id(scsi_qla_host_t *vha, sw_info_t *list)
{
	int		rval = QLA_SUCCESS;
	struct qla_hw_data *ha = vha->hw;
	uint16_t	i;
	struct sns_cmd_pkt	*sns_cmd;

	for (i = 0; i < ha->max_fibre_devices; i++) {
		/* Issue GPN_ID */
		/* Prepare SNS command request. */
		sns_cmd = qla2x00_prep_sns_cmd(vha, GPN_ID_CMD,
		    GPN_ID_SNS_SCMD_LEN, GPN_ID_SNS_DATA_SIZE);

		/* Prepare SNS command arguments -- port_id. */
		sns_cmd->p.cmd.param[0] = list[i].d_id.b.al_pa;
		sns_cmd->p.cmd.param[1] = list[i].d_id.b.area;
		sns_cmd->p.cmd.param[2] = list[i].d_id.b.domain;

		/* Execute SNS command. */
		rval = qla2x00_send_sns(vha, ha->sns_cmd_dma,
		    GPN_ID_SNS_CMD_SIZE / 2, sizeof(struct sns_cmd_pkt));
		if (rval != QLA_SUCCESS) {
			/*EMPTY*/
			ql_dbg(ql_dbg_disc, vha, 0x2032,
			    "GPN_ID Send SNS failed (%d).\n", rval);
		} else if (sns_cmd->p.gpn_data[8] != 0x80 ||
		    sns_cmd->p.gpn_data[9] != 0x02) {
			ql_dbg(ql_dbg_disc + ql_dbg_buffer, vha, 0x207e,
			    "GPN_ID failed, rejected request, gpn_rsp:\n");
			ql_dump_buffer(ql_dbg_disc + ql_dbg_buffer, vha, 0x207f,
			    sns_cmd->p.gpn_data, 16);
			rval = QLA_FUNCTION_FAILED;
		} else {
			/* Save portname */
			memcpy(list[i].port_name, &sns_cmd->p.gpn_data[16],
			    WWN_SIZE);
		}

		/* Last device exit. */
		if (list[i].d_id.b.rsvd_1 != 0)
			break;
	}

	return (rval);
}