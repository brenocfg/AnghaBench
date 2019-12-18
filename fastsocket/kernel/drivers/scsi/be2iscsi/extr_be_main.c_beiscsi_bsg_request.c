#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct iscsi_bsg_request {int msgcode; } ;
struct iscsi_bsg_reply {unsigned short result; int /*<<< orphan*/  reply_payload_rcv_len; } ;
struct TYPE_6__ {int /*<<< orphan*/  sg_cnt; int /*<<< orphan*/  sg_list; } ;
struct TYPE_5__ {int /*<<< orphan*/  payload_len; } ;
struct bsg_job {TYPE_2__ reply_payload; TYPE_1__ request_payload; struct iscsi_bsg_reply* reply; struct iscsi_bsg_request* request; } ;
struct TYPE_7__ {int* mcc_numtag; int /*<<< orphan*/  pdev; int /*<<< orphan*/ * mcc_wait; } ;
struct beiscsi_hba {TYPE_3__ ctrl; } ;
struct be_dma_mem {int /*<<< orphan*/  dma; int /*<<< orphan*/ * va; int /*<<< orphan*/  size; } ;
struct be_cmd_resp_hdr {int /*<<< orphan*/  response_length; } ;
struct Scsi_Host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BEISCSI_HOST_MBX_TIMEOUT ; 
 int /*<<< orphan*/  BEISCSI_LOG_CONFIG ; 
 int EAGAIN ; 
 int EINVAL ; 
 int EIO ; 
 int ENOMEM ; 
#define  ISCSI_BSG_HST_VENDOR 128 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  beiscsi_log (struct beiscsi_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  bsg_job_done (struct bsg_job*,unsigned short,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_mcc_tag (TYPE_3__*,unsigned int) ; 
 struct beiscsi_hba* iscsi_host_priv (struct Scsi_Host*) ; 
 struct Scsi_Host* iscsi_job_to_shost (struct bsg_job*) ; 
 unsigned int mgmt_vendor_specific_fw_cmd (TYPE_3__*,struct beiscsi_hba*,struct bsg_job*,struct be_dma_mem*) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pci_alloc_consistent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_free_consistent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_copy_from_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int wait_event_interruptible_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int beiscsi_bsg_request(struct bsg_job *job)
{
	struct Scsi_Host *shost;
	struct beiscsi_hba *phba;
	struct iscsi_bsg_request *bsg_req = job->request;
	int rc = -EINVAL;
	unsigned int tag;
	struct be_dma_mem nonemb_cmd;
	struct be_cmd_resp_hdr *resp;
	struct iscsi_bsg_reply *bsg_reply = job->reply;
	unsigned short status, extd_status;

	shost = iscsi_job_to_shost(job);
	phba = iscsi_host_priv(shost);

	switch (bsg_req->msgcode) {
	case ISCSI_BSG_HST_VENDOR:
		nonemb_cmd.va = pci_alloc_consistent(phba->ctrl.pdev,
					job->request_payload.payload_len,
					&nonemb_cmd.dma);
		if (nonemb_cmd.va == NULL) {
			beiscsi_log(phba, KERN_ERR, BEISCSI_LOG_CONFIG,
				    "BM_%d : Failed to allocate memory for "
				    "beiscsi_bsg_request\n");
			return -ENOMEM;
		}
		tag = mgmt_vendor_specific_fw_cmd(&phba->ctrl, phba, job,
						  &nonemb_cmd);
		if (!tag) {
			beiscsi_log(phba, KERN_ERR, BEISCSI_LOG_CONFIG,
				    "BM_%d : MBX Tag Allocation Failed\n");

			pci_free_consistent(phba->ctrl.pdev, nonemb_cmd.size,
					    nonemb_cmd.va, nonemb_cmd.dma);
			return -EAGAIN;
		}

		rc = wait_event_interruptible_timeout(
					phba->ctrl.mcc_wait[tag],
					phba->ctrl.mcc_numtag[tag],
					msecs_to_jiffies(
					BEISCSI_HOST_MBX_TIMEOUT));
		extd_status = (phba->ctrl.mcc_numtag[tag] & 0x0000FF00) >> 8;
		status = phba->ctrl.mcc_numtag[tag] & 0x000000FF;
		free_mcc_tag(&phba->ctrl, tag);
		resp = (struct be_cmd_resp_hdr *)nonemb_cmd.va;
		sg_copy_from_buffer(job->reply_payload.sg_list,
				    job->reply_payload.sg_cnt,
				    nonemb_cmd.va, (resp->response_length
				    + sizeof(*resp)));
		bsg_reply->reply_payload_rcv_len = resp->response_length;
		bsg_reply->result = status;
		bsg_job_done(job, bsg_reply->result,
			     bsg_reply->reply_payload_rcv_len);
		pci_free_consistent(phba->ctrl.pdev, nonemb_cmd.size,
				    nonemb_cmd.va, nonemb_cmd.dma);
		if (status || extd_status) {
			beiscsi_log(phba, KERN_ERR, BEISCSI_LOG_CONFIG,
				    "BM_%d : MBX Cmd Failed"
				    " status = %d extd_status = %d\n",
				    status, extd_status);

			return -EIO;
		} else {
			rc = 0;
		}
		break;

	default:
		beiscsi_log(phba, KERN_ERR, BEISCSI_LOG_CONFIG,
				"BM_%d : Unsupported bsg command: 0x%x\n",
				bsg_req->msgcode);
		break;
	}

	return rc;
}