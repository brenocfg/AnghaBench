#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_31__   TYPE_9__ ;
typedef  struct TYPE_30__   TYPE_8__ ;
typedef  struct TYPE_29__   TYPE_7__ ;
typedef  struct TYPE_28__   TYPE_6__ ;
typedef  struct TYPE_27__   TYPE_5__ ;
typedef  struct TYPE_26__   TYPE_4__ ;
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;
typedef  struct TYPE_22__   TYPE_11__ ;
typedef  struct TYPE_21__   TYPE_10__ ;

/* Type definitions */
typedef  size_t uint16_t ;
struct TYPE_30__ {int rsvd_1; int /*<<< orphan*/  al_pa; int /*<<< orphan*/  area; int /*<<< orphan*/  domain; } ;
struct TYPE_31__ {TYPE_8__ b; } ;
struct TYPE_21__ {TYPE_9__ d_id; int /*<<< orphan*/  fp_speed; int /*<<< orphan*/  fabric_port_name; } ;
typedef  TYPE_10__ sw_info_t ;
struct qla_hw_data {size_t max_fibre_devices; int /*<<< orphan*/  ms_iocb_dma; int /*<<< orphan*/  ms_iocb; TYPE_3__* ct_sns; TYPE_1__* isp_ops; } ;
struct TYPE_28__ {struct ct_sns_gid_pt_data* entries; } ;
struct TYPE_29__ {TYPE_6__ gid_pt; } ;
struct ct_sns_rsp {TYPE_7__ rsp; } ;
struct TYPE_26__ {int /*<<< orphan*/  port_type; } ;
struct TYPE_27__ {TYPE_4__ gid_pt; } ;
struct ct_sns_req {TYPE_5__ req; } ;
struct ct_sns_gid_pt_data {int control_byte; int /*<<< orphan*/ * port_id; } ;
struct TYPE_22__ {struct qla_hw_data* hw; } ;
typedef  TYPE_11__ scsi_qla_host_t ;
typedef  int /*<<< orphan*/  ms_iocb_entry_t ;
struct TYPE_24__ {struct ct_sns_rsp rsp; int /*<<< orphan*/  req; } ;
struct TYPE_25__ {TYPE_2__ p; } ;
struct TYPE_23__ {int /*<<< orphan*/ * (* prep_ms_iocb ) (TYPE_11__*,int /*<<< orphan*/ ,size_t) ;} ;

/* Variables and functions */
 int BIT_7 ; 
 int /*<<< orphan*/  GID_PT_CMD ; 
 int /*<<< orphan*/  GID_PT_REQ_SIZE ; 
 scalar_t__ IS_QLA2100 (struct qla_hw_data*) ; 
 scalar_t__ IS_QLA2200 (struct qla_hw_data*) ; 
 int /*<<< orphan*/  NS_NX_PORT_TYPE ; 
 int /*<<< orphan*/  PORT_SPEED_UNKNOWN ; 
 int QLA_FUNCTION_FAILED ; 
 int QLA_SUCCESS ; 
 int /*<<< orphan*/  WWN_SIZE ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ql_dbg (int /*<<< orphan*/ ,TYPE_11__*,int,char*,int) ; 
 int /*<<< orphan*/  ql_dbg_disc ; 
 int qla2x00_chk_ms_status (TYPE_11__*,int /*<<< orphan*/ *,struct ct_sns_rsp*,char*) ; 
 size_t qla2x00_gid_pt_rsp_size (TYPE_11__*) ; 
 int qla2x00_issue_iocb (TYPE_11__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct ct_sns_req* qla2x00_prep_ct_req (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 
 int qla2x00_sns_gid_pt (TYPE_11__*,TYPE_10__*) ; 
 int /*<<< orphan*/ * stub1 (TYPE_11__*,int /*<<< orphan*/ ,size_t) ; 

int
qla2x00_gid_pt(scsi_qla_host_t *vha, sw_info_t *list)
{
	int		rval;
	uint16_t	i;

	ms_iocb_entry_t	*ms_pkt;
	struct ct_sns_req	*ct_req;
	struct ct_sns_rsp	*ct_rsp;

	struct ct_sns_gid_pt_data *gid_data;
	struct qla_hw_data *ha = vha->hw;
	uint16_t gid_pt_rsp_size;

	if (IS_QLA2100(ha) || IS_QLA2200(ha))
		return qla2x00_sns_gid_pt(vha, list);

	gid_data = NULL;
	gid_pt_rsp_size = qla2x00_gid_pt_rsp_size(vha);
	/* Issue GID_PT */
	/* Prepare common MS IOCB */
	ms_pkt = ha->isp_ops->prep_ms_iocb(vha, GID_PT_REQ_SIZE,
	    gid_pt_rsp_size);

	/* Prepare CT request */
	ct_req = qla2x00_prep_ct_req(&ha->ct_sns->p.req, GID_PT_CMD,
	    gid_pt_rsp_size);
	ct_rsp = &ha->ct_sns->p.rsp;

	/* Prepare CT arguments -- port_type */
	ct_req->req.gid_pt.port_type = NS_NX_PORT_TYPE;

	/* Execute MS IOCB */
	rval = qla2x00_issue_iocb(vha, ha->ms_iocb, ha->ms_iocb_dma,
	    sizeof(ms_iocb_entry_t));
	if (rval != QLA_SUCCESS) {
		/*EMPTY*/
		ql_dbg(ql_dbg_disc, vha, 0x2055,
		    "GID_PT issue IOCB failed (%d).\n", rval);
	} else if (qla2x00_chk_ms_status(vha, ms_pkt, ct_rsp, "GID_PT") !=
	    QLA_SUCCESS) {
		rval = QLA_FUNCTION_FAILED;
	} else {
		/* Set port IDs in switch info list. */
		for (i = 0; i < ha->max_fibre_devices; i++) {
			gid_data = &ct_rsp->rsp.gid_pt.entries[i];
			list[i].d_id.b.domain = gid_data->port_id[0];
			list[i].d_id.b.area = gid_data->port_id[1];
			list[i].d_id.b.al_pa = gid_data->port_id[2];
			memset(list[i].fabric_port_name, 0, WWN_SIZE);
			list[i].fp_speed = PORT_SPEED_UNKNOWN;

			/* Last one exit. */
			if (gid_data->control_byte & BIT_7) {
				list[i].d_id.b.rsvd_1 = gid_data->control_byte;
				break;
			}
		}

		/*
		 * If we've used all available slots, then the switch is
		 * reporting back more devices than we can handle with this
		 * single call.  Return a failed status, and let GA_NXT handle
		 * the overload.
		 */
		if (i == ha->max_fibre_devices)
			rval = QLA_FUNCTION_FAILED;
	}

	return (rval);
}