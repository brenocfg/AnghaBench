#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
struct qla_hw_data {int /*<<< orphan*/  ms_iocb_dma; int /*<<< orphan*/  ms_iocb; TYPE_3__* ct_sns; TYPE_1__* isp_ops; } ;
struct ct_sns_rsp {int dummy; } ;
struct TYPE_19__ {scalar_t__ name_len; int /*<<< orphan*/  sym_node_name; int /*<<< orphan*/  node_name; } ;
struct TYPE_20__ {TYPE_4__ rsnn_nn; } ;
struct ct_sns_req {TYPE_5__ req; } ;
struct TYPE_21__ {int /*<<< orphan*/  node_name; struct qla_hw_data* hw; } ;
typedef  TYPE_6__ scsi_qla_host_t ;
struct TYPE_22__ {int /*<<< orphan*/  req_bytecount; int /*<<< orphan*/  dseg_req_length; } ;
typedef  TYPE_7__ ms_iocb_entry_t ;
struct TYPE_17__ {struct ct_sns_rsp rsp; int /*<<< orphan*/  req; } ;
struct TYPE_18__ {TYPE_2__ p; } ;
struct TYPE_16__ {TYPE_7__* (* prep_ms_iocb ) (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 scalar_t__ IS_QLA2100 (struct qla_hw_data*) ; 
 scalar_t__ IS_QLA2200 (struct qla_hw_data*) ; 
 int QLA_FUNCTION_FAILED ; 
 int QLA_SUCCESS ; 
 int /*<<< orphan*/  RSNN_NN_CMD ; 
 int /*<<< orphan*/  RSNN_NN_RSP_SIZE ; 
 int /*<<< orphan*/  WWN_SIZE ; 
 int /*<<< orphan*/  cpu_to_le32 (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ql_dbg (int /*<<< orphan*/ ,TYPE_6__*,int,char*,...) ; 
 int /*<<< orphan*/  ql_dbg_disc ; 
 int qla2x00_chk_ms_status (TYPE_6__*,TYPE_7__*,struct ct_sns_rsp*,char*) ; 
 int /*<<< orphan*/  qla2x00_get_sym_node_name (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int qla2x00_issue_iocb (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct ct_sns_req* qla2x00_prep_ct_req (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 
 TYPE_7__* stub1 (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
qla2x00_rsnn_nn(scsi_qla_host_t *vha)
{
	int		rval;
	struct qla_hw_data *ha = vha->hw;
	ms_iocb_entry_t	*ms_pkt;
	struct ct_sns_req	*ct_req;
	struct ct_sns_rsp	*ct_rsp;

	if (IS_QLA2100(ha) || IS_QLA2200(ha)) {
		ql_dbg(ql_dbg_disc, vha, 0x2050,
		    "RSNN_ID call unsupported on ISP2100/ISP2200.\n");
		return (QLA_SUCCESS);
	}

	/* Issue RSNN_NN */
	/* Prepare common MS IOCB */
	/*   Request size adjusted after CT preparation */
	ms_pkt = ha->isp_ops->prep_ms_iocb(vha, 0, RSNN_NN_RSP_SIZE);

	/* Prepare CT request */
	ct_req = qla2x00_prep_ct_req(&ha->ct_sns->p.req, RSNN_NN_CMD,
	    RSNN_NN_RSP_SIZE);
	ct_rsp = &ha->ct_sns->p.rsp;

	/* Prepare CT arguments -- node_name, symbolic node_name, size */
	memcpy(ct_req->req.rsnn_nn.node_name, vha->node_name, WWN_SIZE);

	/* Prepare the Symbolic Node Name */
	qla2x00_get_sym_node_name(vha, ct_req->req.rsnn_nn.sym_node_name);

	/* Calculate SNN length */
	ct_req->req.rsnn_nn.name_len =
	    (uint8_t)strlen(ct_req->req.rsnn_nn.sym_node_name);

	/* Update MS IOCB request */
	ms_pkt->req_bytecount =
	    cpu_to_le32(24 + 1 + ct_req->req.rsnn_nn.name_len);
	ms_pkt->dseg_req_length = ms_pkt->req_bytecount;

	/* Execute MS IOCB */
	rval = qla2x00_issue_iocb(vha, ha->ms_iocb, ha->ms_iocb_dma,
	    sizeof(ms_iocb_entry_t));
	if (rval != QLA_SUCCESS) {
		/*EMPTY*/
		ql_dbg(ql_dbg_disc, vha, 0x2051,
		    "RSNN_NN issue IOCB failed (%d).\n", rval);
	} else if (qla2x00_chk_ms_status(vha, ms_pkt, ct_rsp, "RSNN_NN") !=
	    QLA_SUCCESS) {
		rval = QLA_FUNCTION_FAILED;
	} else {
		ql_dbg(ql_dbg_disc, vha, 0x2052,
		    "RSNN_NN exiting normally.\n");
	}

	return (rval);
}