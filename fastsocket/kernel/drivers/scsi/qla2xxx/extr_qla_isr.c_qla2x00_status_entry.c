#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_7__ ;
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  size_t uint32_t ;
typedef  size_t uint16_t ;
struct TYPE_21__ {int* rsp_info; int* req_sense_data; int /*<<< orphan*/  status_flags; int /*<<< orphan*/  residual_length; int /*<<< orphan*/  rsp_info_len; int /*<<< orphan*/  req_sense_length; int /*<<< orphan*/  handle; int /*<<< orphan*/  scsi_status; int /*<<< orphan*/  comp_status; } ;
typedef  TYPE_4__ sts_entry_t ;
struct sts_entry_24xx {int* data; int /*<<< orphan*/  ox_id; int /*<<< orphan*/  residual_len; int /*<<< orphan*/  rsp_residual_count; int /*<<< orphan*/  rsp_data_len; int /*<<< orphan*/  sense_len; int /*<<< orphan*/  state_flags; int /*<<< orphan*/  scsi_status; int /*<<< orphan*/  comp_status; } ;
struct scsi_cmnd {unsigned int underflow; int result; int /*<<< orphan*/ * cmnd; TYPE_1__* device; int /*<<< orphan*/  sense_buffer; } ;
struct rsp_que {int /*<<< orphan*/ * status_srb; } ;
struct req_que {size_t num_outstanding_cmds; TYPE_5__** outstanding_cmds; } ;
struct qla_hw_data {int /*<<< orphan*/  max_req_queues; int /*<<< orphan*/  req_qid_map; struct req_que** req_q_map; } ;
struct TYPE_22__ {scalar_t__ type; int /*<<< orphan*/  (* done ) (struct qla_hw_data*,TYPE_5__*,int) ;TYPE_7__* fcport; } ;
typedef  TYPE_5__ srb_t ;
struct TYPE_23__ {int /*<<< orphan*/  host_no; int /*<<< orphan*/  dpc_flags; struct qla_hw_data* hw; } ;
typedef  TYPE_6__ scsi_qla_host_t ;
typedef  size_t int32_t ;
struct TYPE_19__ {int /*<<< orphan*/  al_pa; int /*<<< orphan*/  area; int /*<<< orphan*/  domain; } ;
struct TYPE_20__ {TYPE_2__ b; } ;
struct TYPE_24__ {TYPE_3__ d_id; int /*<<< orphan*/  vha; int /*<<< orphan*/  state; } ;
typedef  TYPE_7__ fc_port_t ;
struct TYPE_18__ {int /*<<< orphan*/  lun; int /*<<< orphan*/  id; int /*<<< orphan*/  vendor; } ;

/* Variables and functions */
 size_t BIT_1 ; 
 size_t BIT_4 ; 
#define  CS_ABORTED 140 
#define  CS_COMPLETE 139 
 size_t CS_DATA_OVERRUN ; 
#define  CS_DATA_UNDERRUN 138 
#define  CS_DIF_ERROR 137 
#define  CS_INCOMPLETE 136 
#define  CS_PORT_BUSY 135 
#define  CS_PORT_CONFIG_CHG 134 
#define  CS_PORT_LOGGED_OUT 133 
#define  CS_PORT_UNAVAILABLE 132 
#define  CS_QUEUE_FULL 131 
#define  CS_RESET 130 
#define  CS_TIMEOUT 129 
#define  CS_TRANSPORT 128 
 int DID_BUS_BUSY ; 
 int DID_ERROR ; 
 int DID_OK ; 
 int DID_RESET ; 
 int DID_TRANSPORT_DISRUPTED ; 
 int /*<<< orphan*/  FCOE_CTX_RESET_NEEDED ; 
 int /*<<< orphan*/  FCS_ONLINE ; 
 struct scsi_cmnd* GET_CMD_SP (TYPE_5__*) ; 
 int /*<<< orphan*/  ISP_ABORT_NEEDED ; 
 scalar_t__ IS_FWI2_CAPABLE (struct qla_hw_data*) ; 
 int /*<<< orphan*/  IS_PI_SPLIT_DET_CAPABLE (struct qla_hw_data*) ; 
 scalar_t__ IS_QLA82XX (struct qla_hw_data*) ; 
 int /*<<< orphan*/  KERN_WARNING ; 
 scalar_t__ LSW (int /*<<< orphan*/ ) ; 
 size_t MSW (int /*<<< orphan*/ ) ; 
 int SAM_STAT_BUSY ; 
 int SAM_STAT_TASK_SET_FULL ; 
 int /*<<< orphan*/  SCSI_SENSE_BUFFERSIZE ; 
 size_t SF_LOGOUT_SENT ; 
 scalar_t__ SRB_BIDI_CMD ; 
 int SS_CHECK_CONDITION ; 
 size_t SS_MASK ; 
 size_t SS_RESIDUAL_OVER ; 
 size_t SS_RESIDUAL_UNDER ; 
 size_t SS_RESPONSE_INFO_LEN_VALID ; 
 size_t SS_SENSE_LEN_VALID ; 
 size_t STATUS_MASK ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 size_t find_first_zero_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  host_to_fcp_swap (int*,int) ; 
 size_t le16_to_cpu (int /*<<< orphan*/ ) ; 
 size_t le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ql_dbg (int /*<<< orphan*/ ,TYPE_6__*,int,char*,...) ; 
 int /*<<< orphan*/  ql_dbg_io ; 
 int /*<<< orphan*/  qla25xx_process_bidir_status_iocb (TYPE_6__*,void*,struct req_que*,size_t) ; 
 int qla2x00_handle_dif_error (TYPE_5__*,struct sts_entry_24xx*) ; 
 int /*<<< orphan*/  qla2x00_handle_sense (TYPE_5__*,int*,size_t,size_t,struct rsp_que*,int) ; 
 int /*<<< orphan*/  qla2x00_mark_device_lost (int /*<<< orphan*/ ,TYPE_7__*,int,int) ; 
 int /*<<< orphan*/  qla2x00_process_completed_request (TYPE_6__*,struct req_que*,size_t) ; 
 int /*<<< orphan*/  qla2xxx_wake_dpc (TYPE_6__*) ; 
 int /*<<< orphan*/  scmd_printk (int /*<<< orphan*/ ,struct scsi_cmnd*,char*,int /*<<< orphan*/ ) ; 
 size_t scsi_bufflen (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  scsi_set_resid (struct scsi_cmnd*,size_t) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct qla_hw_data*,TYPE_5__*,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void
qla2x00_status_entry(scsi_qla_host_t *vha, struct rsp_que *rsp, void *pkt)
{
	srb_t		*sp;
	fc_port_t	*fcport;
	struct scsi_cmnd *cp;
	sts_entry_t *sts;
	struct sts_entry_24xx *sts24;
	uint16_t	comp_status;
	uint16_t	scsi_status;
	uint16_t	ox_id;
	uint8_t		lscsi_status;
	int32_t		resid;
	uint32_t	sense_len, par_sense_len, rsp_info_len, resid_len,
	    fw_resid_len;
	uint8_t		*rsp_info, *sense_data;
	struct qla_hw_data *ha = vha->hw;
	uint32_t handle;
	uint16_t que;
	struct req_que *req;
	int logit = 1;
	int res = 0;
	uint16_t state_flags = 0;

	sts = (sts_entry_t *) pkt;
	sts24 = (struct sts_entry_24xx *) pkt;
	if (IS_FWI2_CAPABLE(ha)) {
		comp_status = le16_to_cpu(sts24->comp_status);
		scsi_status = le16_to_cpu(sts24->scsi_status) & SS_MASK;
		state_flags = le16_to_cpu(sts24->state_flags);
	} else {
		comp_status = le16_to_cpu(sts->comp_status);
		scsi_status = le16_to_cpu(sts->scsi_status) & SS_MASK;
	}
	handle = (uint32_t) LSW(sts->handle);
	que = MSW(sts->handle);
	req = ha->req_q_map[que];

	/* Check for invalid queue pointer */
	if (req == NULL ||
	    que >= find_first_zero_bit(ha->req_qid_map, ha->max_req_queues)) {
		ql_dbg(ql_dbg_io, vha, 0x3059,
		    "Invalid status handle (0x%x): Bad req pointer. req=%p, "
		    "que=%u.\n", sts->handle, req, que);
		return;
	}

	/* Validate handle. */
	if (handle < req->num_outstanding_cmds)
		sp = req->outstanding_cmds[handle];
	else
		sp = NULL;

	if (sp == NULL) {
		ql_dbg(ql_dbg_io, vha, 0x3017,
		    "Invalid status handle (0x%x).\n", sts->handle);

		if (IS_QLA82XX(ha))
			set_bit(FCOE_CTX_RESET_NEEDED, &vha->dpc_flags);
		else
			set_bit(ISP_ABORT_NEEDED, &vha->dpc_flags);
		qla2xxx_wake_dpc(vha);
		return;
	}

	if (unlikely((state_flags & BIT_1) && (sp->type == SRB_BIDI_CMD))) {
		qla25xx_process_bidir_status_iocb(vha, pkt, req, handle);
		return;
	}

	/* Fast path completion. */
	if (comp_status == CS_COMPLETE && scsi_status == 0) {
		qla2x00_process_completed_request(vha, req, handle);

		return;
	}

	req->outstanding_cmds[handle] = NULL;
	cp = GET_CMD_SP(sp);
	if (cp == NULL) {
		ql_dbg(ql_dbg_io, vha, 0x3018,
		    "Command already returned (0x%x/%p).\n",
		    sts->handle, sp);

		return;
	}

	lscsi_status = scsi_status & STATUS_MASK;

	fcport = sp->fcport;

	ox_id = 0;
	sense_len = par_sense_len = rsp_info_len = resid_len =
		fw_resid_len = 0;
	if (IS_FWI2_CAPABLE(ha)) {
		if (scsi_status & SS_SENSE_LEN_VALID)
			sense_len = le32_to_cpu(sts24->sense_len);
		if (scsi_status & SS_RESPONSE_INFO_LEN_VALID)
			rsp_info_len = le32_to_cpu(sts24->rsp_data_len);
		if (scsi_status & (SS_RESIDUAL_UNDER | SS_RESIDUAL_OVER))
			resid_len = le32_to_cpu(sts24->rsp_residual_count);
		if (comp_status == CS_DATA_UNDERRUN)
			fw_resid_len = le32_to_cpu(sts24->residual_len);
		rsp_info = sts24->data;
		sense_data = sts24->data;
		host_to_fcp_swap(sts24->data, sizeof(sts24->data));
		ox_id = le16_to_cpu(sts24->ox_id);
		par_sense_len = sizeof(sts24->data);
	} else {
		if (scsi_status & SS_SENSE_LEN_VALID)
			sense_len = le16_to_cpu(sts->req_sense_length);
		if (scsi_status & SS_RESPONSE_INFO_LEN_VALID)
			rsp_info_len = le16_to_cpu(sts->rsp_info_len);
		resid_len = le32_to_cpu(sts->residual_length);
		rsp_info = sts->rsp_info;
		sense_data = sts->req_sense_data;
		par_sense_len = sizeof(sts->req_sense_data);
	}

	/* Check for any FCP transport errors. */
	if (scsi_status & SS_RESPONSE_INFO_LEN_VALID) {
		/* Sense data lies beyond any FCP RESPONSE data. */
		if (IS_FWI2_CAPABLE(ha)) {
			sense_data += rsp_info_len;
			par_sense_len -= rsp_info_len;
		}
		if (rsp_info_len > 3 && rsp_info[3]) {
			ql_dbg(ql_dbg_io, fcport->vha, 0x3019,
			    "FCP I/O protocol failure (0x%x/0x%x).\n",
			    rsp_info_len, rsp_info[3]);

			res = DID_BUS_BUSY << 16;
			goto out;
		}
	}

	/* Check for overrun. */
	if (IS_FWI2_CAPABLE(ha) && comp_status == CS_COMPLETE &&
	    scsi_status & SS_RESIDUAL_OVER)
		comp_status = CS_DATA_OVERRUN;

	/*
	 * Based on Host and scsi status generate status code for Linux
	 */
	switch (comp_status) {
	case CS_COMPLETE:
	case CS_QUEUE_FULL:
		if (scsi_status == 0) {
			res = DID_OK << 16;
			break;
		}
		if (scsi_status & (SS_RESIDUAL_UNDER | SS_RESIDUAL_OVER)) {
			resid = resid_len;
			scsi_set_resid(cp, resid);

			if (!lscsi_status &&
			    ((unsigned)(scsi_bufflen(cp) - resid) <
			     cp->underflow)) {
				ql_dbg(ql_dbg_io, fcport->vha, 0x301a,
				    "Mid-layer underflow "
				    "detected (0x%x of 0x%x bytes).\n",
				    resid, scsi_bufflen(cp));

				res = DID_ERROR << 16;
				break;
			}
		}
		res = DID_OK << 16 | lscsi_status;

		if (lscsi_status == SAM_STAT_TASK_SET_FULL) {
			ql_dbg(ql_dbg_io, fcport->vha, 0x301b,
			    "QUEUE FULL detected.\n");
			break;
		}
		logit = 0;
		if (lscsi_status != SS_CHECK_CONDITION)
			break;

		memset(cp->sense_buffer, 0, SCSI_SENSE_BUFFERSIZE);
		if (!(scsi_status & SS_SENSE_LEN_VALID))
			break;

		qla2x00_handle_sense(sp, sense_data, par_sense_len, sense_len,
		    rsp, res);
		break;

	case CS_DATA_UNDERRUN:
		/* Use F/W calculated residual length. */
		resid = IS_FWI2_CAPABLE(ha) ? fw_resid_len : resid_len;
		scsi_set_resid(cp, resid);
		if (scsi_status & SS_RESIDUAL_UNDER) {
			if (IS_FWI2_CAPABLE(ha) && fw_resid_len != resid_len) {
				ql_dbg(ql_dbg_io, fcport->vha, 0x301d,
				    "Dropped frame(s) detected "
				    "(0x%x of 0x%x bytes).\n",
				    resid, scsi_bufflen(cp));

				res = DID_ERROR << 16 | lscsi_status;
				goto check_scsi_status;
			}

			if (!lscsi_status &&
			    ((unsigned)(scsi_bufflen(cp) - resid) <
			    cp->underflow)) {
				ql_dbg(ql_dbg_io, fcport->vha, 0x301e,
				    "Mid-layer underflow "
				    "detected (0x%x of 0x%x bytes).\n",
				    resid, scsi_bufflen(cp));

				res = DID_ERROR << 16;
				break;
			}
		} else if (lscsi_status != SAM_STAT_TASK_SET_FULL &&
			    lscsi_status != SAM_STAT_BUSY) {
			/*
			 * scsi status of task set and busy are considered to be
			 * task not completed.
			 */

			ql_dbg(ql_dbg_io, fcport->vha, 0x301f,
			    "Dropped frame(s) detected (0x%x "
			    "of 0x%x bytes).\n", resid,
			    scsi_bufflen(cp));

			res = DID_ERROR << 16 | lscsi_status;
			goto check_scsi_status;
		} else {
			ql_dbg(ql_dbg_io, fcport->vha, 0x3030,
			    "scsi_status: 0x%x, lscsi_status: 0x%x\n",
			    scsi_status, lscsi_status);
		}

		res = DID_OK << 16 | lscsi_status;
		logit = 0;

check_scsi_status:
		/*
		 * Check to see if SCSI Status is non zero. If so report SCSI
		 * Status.
		 */
		if (lscsi_status != 0) {
			if (lscsi_status == SAM_STAT_TASK_SET_FULL) {
				ql_dbg(ql_dbg_io, fcport->vha, 0x3020,
				    "QUEUE FULL detected.\n");
				logit = 1;
				break;
			}
			if (lscsi_status != SS_CHECK_CONDITION)
				break;

			memset(cp->sense_buffer, 0, SCSI_SENSE_BUFFERSIZE);
			if (!(scsi_status & SS_SENSE_LEN_VALID))
				break;

			qla2x00_handle_sense(sp, sense_data, par_sense_len,
			    sense_len, rsp, res);
		}
		break;

	case CS_PORT_LOGGED_OUT:
	case CS_PORT_CONFIG_CHG:
	case CS_PORT_BUSY:
	case CS_INCOMPLETE:
	case CS_PORT_UNAVAILABLE:
	case CS_TIMEOUT:
	case CS_RESET:

		/*
		 * We are going to have the fc class block the rport
		 * while we try to recover so instruct the mid layer
		 * to requeue until the class decides how to handle this.
		 */
		res = DID_TRANSPORT_DISRUPTED << 16;

		if (comp_status == CS_TIMEOUT) {
			if (IS_FWI2_CAPABLE(ha))
				break;
			else if ((le16_to_cpu(sts->status_flags) &
			    SF_LOGOUT_SENT) == 0)
				break;
		}

		ql_dbg(ql_dbg_io, fcport->vha, 0x3021,
		    "Port down status: port-state=0x%x.\n",
		    atomic_read(&fcport->state));

		if (atomic_read(&fcport->state) == FCS_ONLINE)
			qla2x00_mark_device_lost(fcport->vha, fcport, 1, 1);
		break;

	case CS_ABORTED:
		res = DID_RESET << 16;
		break;

	case CS_DIF_ERROR:
		logit = qla2x00_handle_dif_error(sp, sts24);
		res = cp->result;
		break;

	case CS_TRANSPORT:
		res = DID_ERROR << 16;

		if (!IS_PI_SPLIT_DET_CAPABLE(ha))
			break;

		if (state_flags & BIT_4)
			scmd_printk(KERN_WARNING, cp,
			    "Unsupported device '%s' found.\n",
			    cp->device->vendor);
		break;

	default:
		res = DID_ERROR << 16;
		break;
	}

out:
	if (logit)
		ql_dbg(ql_dbg_io, fcport->vha, 0x3022,
		    "FCP command status: 0x%x-0x%x (0x%x) "
		    "nexus=%ld:%d:%d portid=%02x%02x%02x oxid=0x%x "
		    "cdb=%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x len=0x%x "
		    "rsp_info=0x%x resid=0x%x fw_resid=0x%x.\n",
		    comp_status, scsi_status, res, vha->host_no,
		    cp->device->id, cp->device->lun, fcport->d_id.b.domain,
		    fcport->d_id.b.area, fcport->d_id.b.al_pa, ox_id,
		    cp->cmnd[0], cp->cmnd[1], cp->cmnd[2], cp->cmnd[3],
		    cp->cmnd[4], cp->cmnd[5], cp->cmnd[6], cp->cmnd[7],
		    cp->cmnd[8], cp->cmnd[9], scsi_bufflen(cp), rsp_info_len,
		    resid_len, fw_resid_len);

	if (rsp->status_srb == NULL)
		sp->done(ha, sp, res);
}