#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint16_t ;
struct TYPE_13__ {int entry_status; int /*<<< orphan*/  handle; } ;
typedef  TYPE_1__ sts_entry_t ;
struct rsp_que {int dummy; } ;
struct req_que {int dummy; } ;
struct qla_hw_data {size_t max_req_queues; struct req_que** req_q_map; } ;
struct TYPE_14__ {int /*<<< orphan*/  (* done ) (struct qla_hw_data*,TYPE_2__*,int) ;} ;
typedef  TYPE_2__ srb_t ;
struct TYPE_15__ {int /*<<< orphan*/  dpc_flags; struct qla_hw_data* hw; } ;
typedef  TYPE_3__ scsi_qla_host_t ;

/* Variables and functions */
 int DID_BUS_BUSY ; 
 int DID_ERROR ; 
 int /*<<< orphan*/  FCOE_CTX_RESET_NEEDED ; 
 int /*<<< orphan*/  ISP_ABORT_NEEDED ; 
 scalar_t__ IS_QLA82XX (struct qla_hw_data*) ; 
 size_t MSW (int /*<<< orphan*/ ) ; 
 int RF_BUSY ; 
 int /*<<< orphan*/  ql_dbg (int /*<<< orphan*/ ,TYPE_3__*,int,char*,int) ; 
 int /*<<< orphan*/  ql_dbg_async ; 
 int /*<<< orphan*/  ql_log (int /*<<< orphan*/ ,TYPE_3__*,int,char*) ; 
 int /*<<< orphan*/  ql_log_warn ; 
 TYPE_2__* qla2x00_get_sp_from_handle (TYPE_3__*,char const*,struct req_que*,TYPE_1__*) ; 
 int /*<<< orphan*/  qla2xxx_wake_dpc (TYPE_3__*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct qla_hw_data*,TYPE_2__*,int) ; 

__attribute__((used)) static void
qla2x00_error_entry(scsi_qla_host_t *vha, struct rsp_que *rsp, sts_entry_t *pkt)
{
	srb_t *sp;
	struct qla_hw_data *ha = vha->hw;
	const char func[] = "ERROR-IOCB";
	uint16_t que = MSW(pkt->handle);
	struct req_que *req = NULL;
	int res = DID_ERROR << 16;

	ql_dbg(ql_dbg_async, vha, 0x502a,
	    "type of error status in response: 0x%x\n", pkt->entry_status);

	if (que >= ha->max_req_queues || !ha->req_q_map[que])
		goto fatal;

	req = ha->req_q_map[que];

	if (pkt->entry_status & RF_BUSY)
		res = DID_BUS_BUSY << 16;
	sp = qla2x00_get_sp_from_handle(vha, func, req, pkt);
	if (sp) {
		sp->done(ha, sp, res);
		return;
	}
fatal:
	ql_log(ql_log_warn, vha, 0x5030,
	    "Error entry - invalid handle/queue.\n");

	if (IS_QLA82XX(ha))
		set_bit(FCOE_CTX_RESET_NEEDED, &vha->dpc_flags);
	else
		set_bit(ISP_ABORT_NEEDED, &vha->dpc_flags);
	qla2xxx_wake_dpc(vha);
}