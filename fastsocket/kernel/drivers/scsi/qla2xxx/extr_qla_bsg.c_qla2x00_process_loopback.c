#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_34__   TYPE_9__ ;
typedef  struct TYPE_33__   TYPE_8__ ;
typedef  struct TYPE_32__   TYPE_7__ ;
typedef  struct TYPE_31__   TYPE_6__ ;
typedef  struct TYPE_30__   TYPE_5__ ;
typedef  struct TYPE_29__   TYPE_4__ ;
typedef  struct TYPE_28__   TYPE_3__ ;
typedef  struct TYPE_27__   TYPE_2__ ;
typedef  struct TYPE_26__   TYPE_1__ ;
typedef  struct TYPE_25__   TYPE_11__ ;
typedef  struct TYPE_24__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ uint16_t ;
struct qla_hw_data {scalar_t__ current_topology; TYPE_9__* pdev; TYPE_4__* isp_ops; } ;
struct msg_echo_lb {char* req_sg_cnt; char* rsp_sg_cnt; char* options; char* iteration_count; scalar_t__ transfer_size; void* rcv_dma; void* send_dma; } ;
struct fc_bsg_reply {int dummy; } ;
struct TYPE_24__ {scalar_t__ sg_cnt; scalar_t__ payload_len; int /*<<< orphan*/  sg_list; } ;
struct TYPE_33__ {scalar_t__ sg_cnt; int /*<<< orphan*/  sg_list; } ;
struct fc_bsg_job {int reply_len; int /*<<< orphan*/  (* job_done ) (struct fc_bsg_job*) ;TYPE_10__ request_payload; TYPE_8__ reply_payload; TYPE_6__* req; TYPE_5__* reply; TYPE_3__* request; struct Scsi_Host* shost; } ;
struct Scsi_Host {int dummy; } ;
struct TYPE_32__ {int /*<<< orphan*/  online; } ;
struct TYPE_25__ {int /*<<< orphan*/  dpc_flags; int /*<<< orphan*/  loop_state; TYPE_7__ flags; struct qla_hw_data* hw; } ;
typedef  TYPE_11__ scsi_qla_host_t ;
typedef  int /*<<< orphan*/  response ;
typedef  int /*<<< orphan*/  new_config ;
typedef  void* dma_addr_t ;
typedef  int /*<<< orphan*/  config ;
struct TYPE_34__ {int /*<<< orphan*/  dev; } ;
struct TYPE_31__ {scalar_t__ sense; } ;
struct TYPE_30__ {int result; scalar_t__ reply_payload_rcv_len; } ;
struct TYPE_29__ {int /*<<< orphan*/  (* fw_dump ) (TYPE_11__*,int /*<<< orphan*/ ) ;} ;
struct TYPE_26__ {char** vendor_cmd; } ;
struct TYPE_27__ {TYPE_1__ h_vendor; } ;
struct TYPE_28__ {TYPE_2__ rqst_data; } ;

/* Variables and functions */
 int DID_ERROR ; 
 int DID_OK ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int EAGAIN ; 
 int EIO ; 
 scalar_t__ ELS_OPCODE_BYTE ; 
 int ENOMEM ; 
 int EPERM ; 
 char* EXTERNAL_LOOPBACK ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ INTERNAL_LOOPBACK_MASK ; 
 int /*<<< orphan*/  INT_DEF_LB_ECHO_CMD ; 
 int /*<<< orphan*/  INT_DEF_LB_LOOPBACK_CMD ; 
 int /*<<< orphan*/  ISP_ABORT_NEEDED ; 
 scalar_t__ ISP_CFG_F ; 
 scalar_t__ IS_QLA8031 (struct qla_hw_data*) ; 
 scalar_t__ IS_QLA81XX (struct qla_hw_data*) ; 
 scalar_t__ LOOP_READY ; 
 int MAILBOX_REGISTER_COUNT ; 
 scalar_t__ MAX_ELS_FRAME_PAYLOAD ; 
 scalar_t__ MBS_COMMAND_ERROR ; 
 scalar_t__ MBS_LB_RESET ; 
 scalar_t__ QLA_SUCCESS ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dma_alloc_coherent (int /*<<< orphan*/ *,scalar_t__,void**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,void*) ; 
 void* dma_map_sg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_sg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ le32_to_cpu (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,scalar_t__*,int) ; 
 int /*<<< orphan*/  memset (scalar_t__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ql_dbg (int /*<<< orphan*/ ,TYPE_11__*,int,char*,...) ; 
 int /*<<< orphan*/  ql_dbg_user ; 
 int /*<<< orphan*/  ql_log (int /*<<< orphan*/ ,TYPE_11__*,int,char*,...) ; 
 int /*<<< orphan*/  ql_log_warn ; 
 int qla2x00_echo_test (TYPE_11__*,struct msg_echo_lb*,scalar_t__*) ; 
 int qla2x00_loopback_test (TYPE_11__*,struct msg_echo_lb*,scalar_t__*) ; 
 int /*<<< orphan*/  qla2x00_wait_for_chip_reset (TYPE_11__*) ; 
 int /*<<< orphan*/  qla2xxx_wake_dpc (TYPE_11__*) ; 
 scalar_t__ qla81xx_get_port_config (TYPE_11__*,scalar_t__*) ; 
 int qla81xx_reset_loopback_mode (TYPE_11__*,scalar_t__*,int,int) ; 
 scalar_t__ qla81xx_restart_mpi_firmware (TYPE_11__*) ; 
 int qla81xx_set_loopback_mode (TYPE_11__*,scalar_t__*,scalar_t__*,char*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sg_copy_from_buffer (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  sg_copy_to_buffer (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,scalar_t__) ; 
 TYPE_11__* shost_priv (struct Scsi_Host*) ; 
 int /*<<< orphan*/  stub1 (TYPE_11__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct fc_bsg_job*) ; 

__attribute__((used)) static int
qla2x00_process_loopback(struct fc_bsg_job *bsg_job)
{
	struct Scsi_Host *host = bsg_job->shost;
	scsi_qla_host_t *vha = shost_priv(host);
	struct qla_hw_data *ha = vha->hw;
	int rval;
	uint8_t command_sent;
	char *type;
	struct msg_echo_lb elreq;
	uint16_t response[MAILBOX_REGISTER_COUNT];
	uint16_t config[4], new_config[4];
	uint8_t *fw_sts_ptr;
	uint8_t *req_data = NULL;
	dma_addr_t req_data_dma;
	uint32_t req_data_len;
	uint8_t *rsp_data = NULL;
	dma_addr_t rsp_data_dma;
	uint32_t rsp_data_len;

	if (!vha->flags.online) {
		ql_log(ql_log_warn, vha, 0x7019, "Host is not online.\n");
		return -EIO;
	}

	elreq.req_sg_cnt = dma_map_sg(&ha->pdev->dev,
		bsg_job->request_payload.sg_list,
		bsg_job->request_payload.sg_cnt, DMA_TO_DEVICE);

	if (!elreq.req_sg_cnt) {
		ql_log(ql_log_warn, vha, 0x701a,
		    "dma_map_sg returned %d for request.\n", elreq.req_sg_cnt);
		return -ENOMEM;
	}

	elreq.rsp_sg_cnt = dma_map_sg(&ha->pdev->dev,
		bsg_job->reply_payload.sg_list, bsg_job->reply_payload.sg_cnt,
		DMA_FROM_DEVICE);

	if (!elreq.rsp_sg_cnt) {
		ql_log(ql_log_warn, vha, 0x701b,
		    "dma_map_sg returned %d for reply.\n", elreq.rsp_sg_cnt);
		rval = -ENOMEM;
		goto done_unmap_req_sg;
	}

	if ((elreq.req_sg_cnt != bsg_job->request_payload.sg_cnt) ||
		(elreq.rsp_sg_cnt != bsg_job->reply_payload.sg_cnt)) {
		ql_log(ql_log_warn, vha, 0x701c,
		    "dma mapping resulted in different sg counts, "
		    "request_sg_cnt: %x dma_request_sg_cnt: %x "
		    "reply_sg_cnt: %x dma_reply_sg_cnt: %x.\n",
		    bsg_job->request_payload.sg_cnt, elreq.req_sg_cnt,
		    bsg_job->reply_payload.sg_cnt, elreq.rsp_sg_cnt);

		rval = -EAGAIN;
		goto done_unmap_sg;
	}
	req_data_len = rsp_data_len = bsg_job->request_payload.payload_len;
	req_data = dma_alloc_coherent(&ha->pdev->dev, req_data_len,
		&req_data_dma, GFP_KERNEL);
	if (!req_data) {
		ql_log(ql_log_warn, vha, 0x701d,
		    "dma alloc failed for req_data.\n");
		rval = -ENOMEM;
		goto done_unmap_sg;
	}

	rsp_data = dma_alloc_coherent(&ha->pdev->dev, rsp_data_len,
		&rsp_data_dma, GFP_KERNEL);
	if (!rsp_data) {
		ql_log(ql_log_warn, vha, 0x7004,
		    "dma alloc failed for rsp_data.\n");
		rval = -ENOMEM;
		goto done_free_dma_req;
	}

	/* Copy the request buffer in req_data now */
	sg_copy_to_buffer(bsg_job->request_payload.sg_list,
		bsg_job->request_payload.sg_cnt, req_data, req_data_len);

	elreq.send_dma = req_data_dma;
	elreq.rcv_dma = rsp_data_dma;
	elreq.transfer_size = req_data_len;

	elreq.options = bsg_job->request->rqst_data.h_vendor.vendor_cmd[1];
	elreq.iteration_count =
	    bsg_job->request->rqst_data.h_vendor.vendor_cmd[2];

	if (atomic_read(&vha->loop_state) == LOOP_READY &&
	    (ha->current_topology == ISP_CFG_F ||
	    ((IS_QLA81XX(ha) || IS_QLA8031(ha)) &&
	    le32_to_cpu(*(uint32_t *)req_data) == ELS_OPCODE_BYTE
	    && req_data_len == MAX_ELS_FRAME_PAYLOAD)) &&
	    elreq.options == EXTERNAL_LOOPBACK) {
		type = "FC_BSG_HST_VENDOR_ECHO_DIAG";
		ql_dbg(ql_dbg_user, vha, 0x701e,
		    "BSG request type: %s.\n", type);
		command_sent = INT_DEF_LB_ECHO_CMD;
		rval = qla2x00_echo_test(vha, &elreq, response);
       } else {
		if (IS_QLA81XX(ha) || IS_QLA8031(ha)) {
			memset(config, 0, sizeof(config));
			memset(new_config, 0, sizeof(new_config));

			if (qla81xx_get_port_config(vha, config)) {
				ql_log(ql_log_warn, vha, 0x701f,
				    "Get port config failed.\n");
				rval = -EPERM;
				goto done_free_dma_rsp;
			}

			if ((config[0] & INTERNAL_LOOPBACK_MASK) != 0) {
				ql_dbg(ql_dbg_user, vha, 0x70c4,
				    "Loopback operation already in "
				    "progress.\n");
				rval = -EAGAIN;
				goto done_free_dma_rsp;
			}

			ql_dbg(ql_dbg_user, vha, 0x70c0,
			    "elreq.options=%04x\n", elreq.options);

			if (elreq.options == EXTERNAL_LOOPBACK)
				if (IS_QLA8031(ha))
					rval = qla81xx_set_loopback_mode(vha,
					    config, new_config, elreq.options);
				else
					rval = qla81xx_reset_loopback_mode(vha,
					    config, 1, 0);
			else
				rval = qla81xx_set_loopback_mode(vha, config,
				    new_config, elreq.options);

			if (rval) {
				rval = -EPERM;
				goto done_free_dma_rsp;
			}

			type = "FC_BSG_HST_VENDOR_LOOPBACK";
			ql_dbg(ql_dbg_user, vha, 0x7028,
			    "BSG request type: %s.\n", type);

			command_sent = INT_DEF_LB_LOOPBACK_CMD;
			rval = qla2x00_loopback_test(vha, &elreq, response);

			if (response[0] == MBS_COMMAND_ERROR &&
					response[1] == MBS_LB_RESET) {
				ql_log(ql_log_warn, vha, 0x7029,
				    "MBX command error, Aborting ISP.\n");
				set_bit(ISP_ABORT_NEEDED, &vha->dpc_flags);
				qla2xxx_wake_dpc(vha);
				qla2x00_wait_for_chip_reset(vha);
				/* Also reset the MPI */
				if (IS_QLA81XX(ha)) {
					if (qla81xx_restart_mpi_firmware(vha) !=
					    QLA_SUCCESS) {
						ql_log(ql_log_warn, vha, 0x702a,
						    "MPI reset failed.\n");
					}
				}

				rval = -EIO;
				goto done_free_dma_rsp;
			}

			if (new_config[0]) {
				int ret;

				/* Revert back to original port config
				 * Also clear internal loopback
				 */
				ret = qla81xx_reset_loopback_mode(vha,
				    new_config, 0, 1);
				if (ret) {
					/*
					 * If the reset of the loopback mode
					 * doesn't work take FCoE dump and then
					 * reset the chip.
					 */
					ha->isp_ops->fw_dump(vha, 0);
					set_bit(ISP_ABORT_NEEDED,
					    &vha->dpc_flags);
				}

			}

		} else {
			type = "FC_BSG_HST_VENDOR_LOOPBACK";
			ql_dbg(ql_dbg_user, vha, 0x702b,
			    "BSG request type: %s.\n", type);
			command_sent = INT_DEF_LB_LOOPBACK_CMD;
			rval = qla2x00_loopback_test(vha, &elreq, response);
		}
	}

	if (rval) {
		ql_log(ql_log_warn, vha, 0x702c,
		    "Vendor request %s failed.\n", type);

		rval = 0;
		bsg_job->reply->result = (DID_ERROR << 16);
		bsg_job->reply->reply_payload_rcv_len = 0;
	} else {
		ql_dbg(ql_dbg_user, vha, 0x702d,
		    "Vendor request %s completed.\n", type);
		bsg_job->reply->result = (DID_OK << 16);
		sg_copy_from_buffer(bsg_job->reply_payload.sg_list,
			bsg_job->reply_payload.sg_cnt, rsp_data,
			rsp_data_len);
	}

	bsg_job->reply_len = sizeof(struct fc_bsg_reply) +
	    sizeof(response) + sizeof(uint8_t);
	fw_sts_ptr = ((uint8_t *)bsg_job->req->sense) +
	    sizeof(struct fc_bsg_reply);
	memcpy(fw_sts_ptr, response, sizeof(response));
	fw_sts_ptr += sizeof(response);
	*fw_sts_ptr = command_sent;

done_free_dma_rsp:
	dma_free_coherent(&ha->pdev->dev, rsp_data_len,
		rsp_data, rsp_data_dma);
done_free_dma_req:
	dma_free_coherent(&ha->pdev->dev, req_data_len,
		req_data, req_data_dma);
done_unmap_sg:
	dma_unmap_sg(&ha->pdev->dev,
	    bsg_job->reply_payload.sg_list,
	    bsg_job->reply_payload.sg_cnt, DMA_FROM_DEVICE);
done_unmap_req_sg:
	dma_unmap_sg(&ha->pdev->dev,
	    bsg_job->request_payload.sg_list,
	    bsg_job->request_payload.sg_cnt, DMA_TO_DEVICE);
	if (!rval)
		bsg_job->job_done(bsg_job);
	return rval;
}