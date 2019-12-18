#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
typedef  int uint16_t ;
struct verify_chip_entry_84xx {int entry_count; void* data_seg_cnt; void* dseg_length; void** dseg_address; void* fw_seq_size; void* fw_size; void* fw_ver; void* options; int /*<<< orphan*/  entry_type; } ;
struct qla_hw_data {TYPE_5__* pdev; int /*<<< orphan*/  s_dma_pool; } ;
struct fc_bsg_reply {int dummy; } ;
struct TYPE_17__ {scalar_t__ sg_cnt; scalar_t__ payload_len; int /*<<< orphan*/  sg_list; } ;
struct fc_bsg_job {int reply_len; int /*<<< orphan*/  (* job_done ) (struct fc_bsg_job*) ;TYPE_6__ request_payload; TYPE_4__* reply; TYPE_3__* request; struct Scsi_Host* shost; } ;
struct access_chip_84xx {int dummy; } ;
struct Scsi_Host {int dummy; } ;
struct TYPE_18__ {struct qla_hw_data* hw; } ;
typedef  TYPE_7__ scsi_qla_host_t ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_16__ {int /*<<< orphan*/  dev; } ;
struct TYPE_15__ {int /*<<< orphan*/  result; } ;
struct TYPE_12__ {scalar_t__* vendor_cmd; } ;
struct TYPE_13__ {TYPE_1__ h_vendor; } ;
struct TYPE_14__ {TYPE_2__ rqst_data; } ;

/* Variables and functions */
 scalar_t__ A84_ISSUE_UPDATE_DIAGFW_CMD ; 
 int DID_ERROR ; 
 int /*<<< orphan*/  DID_OK ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int EAGAIN ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IS_QLA84XX (struct qla_hw_data*) ; 
 scalar_t__ LSD (int /*<<< orphan*/ ) ; 
 scalar_t__ MSD (int /*<<< orphan*/ ) ; 
 int VCO_DIAG_FW ; 
 int VCO_END_OF_DATA ; 
 int VCO_FORCE_UPDATE ; 
 int /*<<< orphan*/  VERIFY_CHIP_IOCB_TYPE ; 
 void* cpu_to_le16 (int) ; 
 void* cpu_to_le32 (scalar_t__) ; 
 void* dma_alloc_coherent (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,scalar_t__,void*,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_map_sg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 struct verify_chip_entry_84xx* dma_pool_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_pool_free (int /*<<< orphan*/ ,struct verify_chip_entry_84xx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_sg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ le32_to_cpu (scalar_t__) ; 
 int /*<<< orphan*/  memset (struct verify_chip_entry_84xx*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ql_dbg (int /*<<< orphan*/ ,TYPE_7__*,int,char*) ; 
 int /*<<< orphan*/  ql_dbg_user ; 
 int /*<<< orphan*/  ql_log (int /*<<< orphan*/ ,TYPE_7__*,int,char*,...) ; 
 int /*<<< orphan*/  ql_log_warn ; 
 int qla2x00_issue_iocb_timeout (TYPE_7__*,struct verify_chip_entry_84xx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sg_copy_to_buffer (int /*<<< orphan*/ ,scalar_t__,void*,scalar_t__) ; 
 TYPE_7__* shost_priv (struct Scsi_Host*) ; 
 int /*<<< orphan*/  stub1 (struct fc_bsg_job*) ; 

__attribute__((used)) static int
qla84xx_updatefw(struct fc_bsg_job *bsg_job)
{
	struct Scsi_Host *host = bsg_job->shost;
	scsi_qla_host_t *vha = shost_priv(host);
	struct qla_hw_data *ha = vha->hw;
	struct verify_chip_entry_84xx *mn = NULL;
	dma_addr_t mn_dma, fw_dma;
	void *fw_buf = NULL;
	int rval = 0;
	uint32_t sg_cnt;
	uint32_t data_len;
	uint16_t options;
	uint32_t flag;
	uint32_t fw_ver;

	if (!IS_QLA84XX(ha)) {
		ql_dbg(ql_dbg_user, vha, 0x7032,
		    "Not 84xx, exiting.\n");
		return -EINVAL;
	}

	sg_cnt = dma_map_sg(&ha->pdev->dev, bsg_job->request_payload.sg_list,
		bsg_job->request_payload.sg_cnt, DMA_TO_DEVICE);
	if (!sg_cnt) {
		ql_log(ql_log_warn, vha, 0x7033,
		    "dma_map_sg returned %d for request.\n", sg_cnt);
		return -ENOMEM;
	}

	if (sg_cnt != bsg_job->request_payload.sg_cnt) {
		ql_log(ql_log_warn, vha, 0x7034,
		    "DMA mapping resulted in different sg counts, "
		    "request_sg_cnt: %x dma_request_sg_cnt: %x.\n",
		    bsg_job->request_payload.sg_cnt, sg_cnt);
		rval = -EAGAIN;
		goto done_unmap_sg;
	}

	data_len = bsg_job->request_payload.payload_len;
	fw_buf = dma_alloc_coherent(&ha->pdev->dev, data_len,
		&fw_dma, GFP_KERNEL);
	if (!fw_buf) {
		ql_log(ql_log_warn, vha, 0x7035,
		    "DMA alloc failed for fw_buf.\n");
		rval = -ENOMEM;
		goto done_unmap_sg;
	}

	sg_copy_to_buffer(bsg_job->request_payload.sg_list,
		bsg_job->request_payload.sg_cnt, fw_buf, data_len);

	mn = dma_pool_alloc(ha->s_dma_pool, GFP_KERNEL, &mn_dma);
	if (!mn) {
		ql_log(ql_log_warn, vha, 0x7036,
		    "DMA alloc failed for fw buffer.\n");
		rval = -ENOMEM;
		goto done_free_fw_buf;
	}

	flag = bsg_job->request->rqst_data.h_vendor.vendor_cmd[1];
	fw_ver = le32_to_cpu(*((uint32_t *)((uint32_t *)fw_buf + 2)));

	memset(mn, 0, sizeof(struct access_chip_84xx));
	mn->entry_type = VERIFY_CHIP_IOCB_TYPE;
	mn->entry_count = 1;

	options = VCO_FORCE_UPDATE | VCO_END_OF_DATA;
	if (flag == A84_ISSUE_UPDATE_DIAGFW_CMD)
		options |= VCO_DIAG_FW;

	mn->options = cpu_to_le16(options);
	mn->fw_ver =  cpu_to_le32(fw_ver);
	mn->fw_size =  cpu_to_le32(data_len);
	mn->fw_seq_size =  cpu_to_le32(data_len);
	mn->dseg_address[0] = cpu_to_le32(LSD(fw_dma));
	mn->dseg_address[1] = cpu_to_le32(MSD(fw_dma));
	mn->dseg_length = cpu_to_le32(data_len);
	mn->data_seg_cnt = cpu_to_le16(1);

	rval = qla2x00_issue_iocb_timeout(vha, mn, mn_dma, 0, 120);

	if (rval) {
		ql_log(ql_log_warn, vha, 0x7037,
		    "Vendor request 84xx updatefw failed.\n");

		rval = (DID_ERROR << 16);
	} else {
		ql_dbg(ql_dbg_user, vha, 0x7038,
		    "Vendor request 84xx updatefw completed.\n");

		bsg_job->reply_len = sizeof(struct fc_bsg_reply);
		bsg_job->reply->result = DID_OK;
	}

	dma_pool_free(ha->s_dma_pool, mn, mn_dma);

done_free_fw_buf:
	dma_free_coherent(&ha->pdev->dev, data_len, fw_buf, fw_dma);

done_unmap_sg:
	dma_unmap_sg(&ha->pdev->dev, bsg_job->request_payload.sg_list,
		bsg_job->request_payload.sg_cnt, DMA_TO_DEVICE);

	if (!rval)
		bsg_job->job_done(bsg_job);
	return rval;
}