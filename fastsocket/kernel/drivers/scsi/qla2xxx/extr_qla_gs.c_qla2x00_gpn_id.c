#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_30__   TYPE_9__ ;
typedef  struct TYPE_29__   TYPE_8__ ;
typedef  struct TYPE_28__   TYPE_7__ ;
typedef  struct TYPE_27__   TYPE_6__ ;
typedef  struct TYPE_26__   TYPE_5__ ;
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;
typedef  struct TYPE_21__   TYPE_11__ ;
typedef  struct TYPE_20__   TYPE_10__ ;

/* Type definitions */
typedef  size_t uint16_t ;
struct TYPE_29__ {scalar_t__ rsvd_1; int /*<<< orphan*/  al_pa; int /*<<< orphan*/  area; int /*<<< orphan*/  domain; } ;
struct TYPE_30__ {TYPE_8__ b; } ;
struct TYPE_20__ {TYPE_9__ d_id; int /*<<< orphan*/  port_name; } ;
typedef  TYPE_10__ sw_info_t ;
struct qla_hw_data {size_t max_fibre_devices; int /*<<< orphan*/  ms_iocb_dma; int /*<<< orphan*/  ms_iocb; TYPE_3__* ct_sns; TYPE_1__* isp_ops; } ;
struct TYPE_27__ {int /*<<< orphan*/  port_name; } ;
struct TYPE_28__ {TYPE_6__ gpn_id; } ;
struct ct_sns_rsp {TYPE_7__ rsp; } ;
struct TYPE_25__ {int /*<<< orphan*/ * port_id; } ;
struct TYPE_26__ {TYPE_4__ port_id; } ;
struct ct_sns_req {TYPE_5__ req; } ;
struct TYPE_21__ {struct qla_hw_data* hw; } ;
typedef  TYPE_11__ scsi_qla_host_t ;
typedef  int /*<<< orphan*/  ms_iocb_entry_t ;
struct TYPE_23__ {struct ct_sns_rsp rsp; int /*<<< orphan*/  req; } ;
struct TYPE_24__ {TYPE_2__ p; } ;
struct TYPE_22__ {int /*<<< orphan*/ * (* prep_ms_iocb ) (TYPE_11__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  GPN_ID_CMD ; 
 int /*<<< orphan*/  GPN_ID_REQ_SIZE ; 
 int /*<<< orphan*/  GPN_ID_RSP_SIZE ; 
 scalar_t__ IS_QLA2100 (struct qla_hw_data*) ; 
 scalar_t__ IS_QLA2200 (struct qla_hw_data*) ; 
 int QLA_FUNCTION_FAILED ; 
 int QLA_SUCCESS ; 
 int /*<<< orphan*/  WWN_SIZE ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ql_dbg (int /*<<< orphan*/ ,TYPE_11__*,int,char*,int) ; 
 int /*<<< orphan*/  ql_dbg_disc ; 
 int qla2x00_chk_ms_status (TYPE_11__*,int /*<<< orphan*/ *,struct ct_sns_rsp*,char*) ; 
 int qla2x00_issue_iocb (TYPE_11__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct ct_sns_req* qla2x00_prep_ct_req (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int qla2x00_sns_gpn_id (TYPE_11__*,TYPE_10__*) ; 
 int /*<<< orphan*/ * stub1 (TYPE_11__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
qla2x00_gpn_id(scsi_qla_host_t *vha, sw_info_t *list)
{
	int		rval = QLA_SUCCESS;
	uint16_t	i;

	ms_iocb_entry_t	*ms_pkt;
	struct ct_sns_req	*ct_req;
	struct ct_sns_rsp	*ct_rsp;
	struct qla_hw_data *ha = vha->hw;

	if (IS_QLA2100(ha) || IS_QLA2200(ha))
		return qla2x00_sns_gpn_id(vha, list);

	for (i = 0; i < ha->max_fibre_devices; i++) {
		/* Issue GPN_ID */
		/* Prepare common MS IOCB */
		ms_pkt = ha->isp_ops->prep_ms_iocb(vha, GPN_ID_REQ_SIZE,
		    GPN_ID_RSP_SIZE);

		/* Prepare CT request */
		ct_req = qla2x00_prep_ct_req(&ha->ct_sns->p.req, GPN_ID_CMD,
		    GPN_ID_RSP_SIZE);
		ct_rsp = &ha->ct_sns->p.rsp;

		/* Prepare CT arguments -- port_id */
		ct_req->req.port_id.port_id[0] = list[i].d_id.b.domain;
		ct_req->req.port_id.port_id[1] = list[i].d_id.b.area;
		ct_req->req.port_id.port_id[2] = list[i].d_id.b.al_pa;

		/* Execute MS IOCB */
		rval = qla2x00_issue_iocb(vha, ha->ms_iocb, ha->ms_iocb_dma,
		    sizeof(ms_iocb_entry_t));
		if (rval != QLA_SUCCESS) {
			/*EMPTY*/
			ql_dbg(ql_dbg_disc, vha, 0x2056,
			    "GPN_ID issue IOCB failed (%d).\n", rval);
			break;
		} else if (qla2x00_chk_ms_status(vha, ms_pkt, ct_rsp,
		    "GPN_ID") != QLA_SUCCESS) {
			rval = QLA_FUNCTION_FAILED;
			break;
		} else {
			/* Save portname */
			memcpy(list[i].port_name,
			    ct_rsp->rsp.gpn_id.port_name, WWN_SIZE);
		}

		/* Last device exit. */
		if (list[i].d_id.b.rsvd_1 != 0)
			break;
	}

	return (rval);
}