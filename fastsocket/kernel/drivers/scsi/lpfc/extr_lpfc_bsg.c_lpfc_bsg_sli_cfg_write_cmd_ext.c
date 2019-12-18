#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_35__   TYPE_9__ ;
typedef  struct TYPE_34__   TYPE_8__ ;
typedef  struct TYPE_33__   TYPE_7__ ;
typedef  struct TYPE_32__   TYPE_6__ ;
typedef  struct TYPE_31__   TYPE_5__ ;
typedef  struct TYPE_30__   TYPE_4__ ;
typedef  struct TYPE_29__   TYPE_3__ ;
typedef  struct TYPE_28__   TYPE_2__ ;
typedef  struct TYPE_27__   TYPE_1__ ;
typedef  struct TYPE_26__   TYPE_15__ ;
typedef  struct TYPE_25__   TYPE_14__ ;
typedef  struct TYPE_24__   TYPE_13__ ;
typedef  struct TYPE_23__   TYPE_12__ ;
typedef  struct TYPE_22__   TYPE_11__ ;
typedef  struct TYPE_21__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct TYPE_33__ {int hbd_count; int /*<<< orphan*/ * hbd; } ;
struct TYPE_32__ {TYPE_5__* mse; int /*<<< orphan*/  sli_config_hdr; } ;
struct TYPE_34__ {TYPE_7__ sli_config_emb1_subsys; TYPE_6__ sli_config_emb0_subsys; } ;
struct lpfc_sli_config_mbox {TYPE_8__ un; } ;
struct TYPE_23__ {int nembType; int numBuf; int /*<<< orphan*/  state; struct lpfc_dmabuf* mbx_dmabuf; int /*<<< orphan*/  seqNum; int /*<<< orphan*/  mbxTag; int /*<<< orphan*/  mboxType; } ;
struct TYPE_30__ {int /*<<< orphan*/  sli_intf; } ;
struct lpfc_hba {int /*<<< orphan*/  mbox_mem_pool; TYPE_12__ mbox_ext_buf_ctx; int /*<<< orphan*/  pport; TYPE_4__ sli4_hba; } ;
struct lpfc_dmabuf {scalar_t__ virt; } ;
struct fc_bsg_job {int /*<<< orphan*/  (* job_done ) (struct fc_bsg_job*) ;TYPE_13__* reply; struct bsg_job_data* dd_data; TYPE_3__* request; } ;
struct dfc_mbox_req {int /*<<< orphan*/  extSeqNum; int /*<<< orphan*/  extMboxTag; } ;
struct TYPE_21__ {TYPE_14__* mb; TYPE_15__* pmboxq; } ;
struct TYPE_22__ {TYPE_10__ mbox; } ;
struct bsg_job_data {TYPE_11__ context_un; struct fc_bsg_job* set_job; int /*<<< orphan*/  type; } ;
typedef  enum nemb_type { ____Placeholder_nemb_type } nemb_type ;
struct TYPE_25__ {int /*<<< orphan*/  mbxOwner; } ;
struct TYPE_35__ {TYPE_14__ mb; } ;
struct TYPE_31__ {int /*<<< orphan*/  buf_len; } ;
struct TYPE_27__ {scalar_t__ vendor_cmd; } ;
struct TYPE_28__ {TYPE_1__ h_vendor; } ;
struct TYPE_29__ {TYPE_2__ rqst_data; } ;
struct TYPE_26__ {struct bsg_job_data* context1; int /*<<< orphan*/  mbox_cmpl; int /*<<< orphan*/  vport; TYPE_9__ u; } ;
struct TYPE_24__ {scalar_t__ result; } ;
typedef  TYPE_14__ MAILBOX_t ;
typedef  TYPE_15__ LPFC_MBOXQ_t ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int EPERM ; 
 int EPIPE ; 
 int ERANGE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  LOG_LIBDFC ; 
 int /*<<< orphan*/  LPFC_BSG_MBOX_PORT ; 
 int LPFC_MBX_SLI_CONFIG_MAX_HBD ; 
 int LPFC_MBX_SLI_CONFIG_MAX_MSE ; 
 scalar_t__ LPFC_SLI_INTF_IF_TYPE_2 ; 
 int MBX_BUSY ; 
 int /*<<< orphan*/  MBX_NOWAIT ; 
 int MBX_SUCCESS ; 
 int /*<<< orphan*/  OWN_HOST ; 
 int SLI_CONFIG_HANDLED ; 
 int SLI_CONFIG_NOT_HANDLED ; 
 int /*<<< orphan*/  TYPE_MBOX ; 
 scalar_t__ bf_get (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int bsg_bf_get (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_mbox ; 
 int /*<<< orphan*/  kfree (struct bsg_job_data*) ; 
 struct bsg_job_data* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_bsg_issue_write_mbox_ext_cmpl ; 
 int /*<<< orphan*/  lpfc_bsg_sli_cfg_dma_desc_setup (struct lpfc_hba*,int,int /*<<< orphan*/ ,struct lpfc_dmabuf*,struct lpfc_dmabuf*) ; 
 int /*<<< orphan*/  lpfc_idiag_mbxacc_dump_bsg_mbox (struct lpfc_hba*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct lpfc_dmabuf*,int) ; 
 int /*<<< orphan*/  lpfc_mbox_hdr_mse_cnt ; 
 int /*<<< orphan*/  lpfc_mbox_sli_config_ecmn_hbd_len ; 
 int /*<<< orphan*/  lpfc_printf_log (struct lpfc_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  lpfc_sli_intf_if_type ; 
 int lpfc_sli_issue_mbox (struct lpfc_hba*,TYPE_15__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbox_wr ; 
 int /*<<< orphan*/  memcpy (TYPE_14__*,int /*<<< orphan*/ *,int) ; 
 TYPE_15__* mempool_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mempool_free (TYPE_15__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_15__*,int /*<<< orphan*/ ,int) ; 
 int nemb_mse ; 
 int /*<<< orphan*/  sta_pos_addr ; 
 int /*<<< orphan*/  sta_pre_addr ; 
 int /*<<< orphan*/  stub1 (struct fc_bsg_job*) ; 

__attribute__((used)) static int
lpfc_bsg_sli_cfg_write_cmd_ext(struct lpfc_hba *phba, struct fc_bsg_job *job,
			       enum nemb_type nemb_tp,
			       struct lpfc_dmabuf *dmabuf)
{
	struct dfc_mbox_req *mbox_req;
	struct lpfc_sli_config_mbox *sli_cfg_mbx;
	uint32_t ext_buf_cnt;
	struct bsg_job_data *dd_data = NULL;
	LPFC_MBOXQ_t *pmboxq = NULL;
	MAILBOX_t *pmb;
	uint8_t *mbx;
	int rc = SLI_CONFIG_NOT_HANDLED, i;

	mbox_req =
	   (struct dfc_mbox_req *)job->request->rqst_data.h_vendor.vendor_cmd;

	/* pointer to the start of mailbox command */
	sli_cfg_mbx = (struct lpfc_sli_config_mbox *)dmabuf->virt;

	if (nemb_tp == nemb_mse) {
		ext_buf_cnt = bsg_bf_get(lpfc_mbox_hdr_mse_cnt,
			&sli_cfg_mbx->un.sli_config_emb0_subsys.sli_config_hdr);
		if (ext_buf_cnt > LPFC_MBX_SLI_CONFIG_MAX_MSE) {
			lpfc_printf_log(phba, KERN_ERR, LOG_LIBDFC,
					"2953 Failed SLI_CONFIG(mse) wr, "
					"ext_buf_cnt(%d) out of range(%d)\n",
					ext_buf_cnt,
					LPFC_MBX_SLI_CONFIG_MAX_MSE);
			return -ERANGE;
		}
		lpfc_printf_log(phba, KERN_INFO, LOG_LIBDFC,
				"2949 Handled SLI_CONFIG(mse) wr, "
				"ext_buf_cnt:%d\n", ext_buf_cnt);
	} else {
		/* sanity check on interface type for support */
		if (bf_get(lpfc_sli_intf_if_type, &phba->sli4_hba.sli_intf) !=
		    LPFC_SLI_INTF_IF_TYPE_2)
			return -ENODEV;
		/* nemb_tp == nemb_hbd */
		ext_buf_cnt = sli_cfg_mbx->un.sli_config_emb1_subsys.hbd_count;
		if (ext_buf_cnt > LPFC_MBX_SLI_CONFIG_MAX_HBD) {
			lpfc_printf_log(phba, KERN_ERR, LOG_LIBDFC,
					"2954 Failed SLI_CONFIG(hbd) wr, "
					"ext_buf_cnt(%d) out of range(%d)\n",
					ext_buf_cnt,
					LPFC_MBX_SLI_CONFIG_MAX_HBD);
			return -ERANGE;
		}
		lpfc_printf_log(phba, KERN_INFO, LOG_LIBDFC,
				"2950 Handled SLI_CONFIG(hbd) wr, "
				"ext_buf_cnt:%d\n", ext_buf_cnt);
	}

	/* before dma buffer descriptor setup */
	lpfc_idiag_mbxacc_dump_bsg_mbox(phba, nemb_tp, mbox_wr, dma_mbox,
					sta_pre_addr, dmabuf, ext_buf_cnt);

	if (ext_buf_cnt == 0)
		return -EPERM;

	/* for the first external buffer */
	lpfc_bsg_sli_cfg_dma_desc_setup(phba, nemb_tp, 0, dmabuf, dmabuf);

	/* after dma descriptor setup */
	lpfc_idiag_mbxacc_dump_bsg_mbox(phba, nemb_tp, mbox_wr, dma_mbox,
					sta_pos_addr, dmabuf, ext_buf_cnt);

	/* log for looking forward */
	for (i = 1; i < ext_buf_cnt; i++) {
		if (nemb_tp == nemb_mse)
			lpfc_printf_log(phba, KERN_INFO, LOG_LIBDFC,
				"2951 SLI_CONFIG(mse), buf[%d]-length:%d\n",
				i, sli_cfg_mbx->un.sli_config_emb0_subsys.
				mse[i].buf_len);
		else
			lpfc_printf_log(phba, KERN_INFO, LOG_LIBDFC,
				"2952 SLI_CONFIG(hbd), buf[%d]-length:%d\n",
				i, bsg_bf_get(lpfc_mbox_sli_config_ecmn_hbd_len,
				&sli_cfg_mbx->un.sli_config_emb1_subsys.
				hbd[i]));
	}

	/* multi-buffer handling context */
	phba->mbox_ext_buf_ctx.nembType = nemb_tp;
	phba->mbox_ext_buf_ctx.mboxType = mbox_wr;
	phba->mbox_ext_buf_ctx.numBuf = ext_buf_cnt;
	phba->mbox_ext_buf_ctx.mbxTag = mbox_req->extMboxTag;
	phba->mbox_ext_buf_ctx.seqNum = mbox_req->extSeqNum;
	phba->mbox_ext_buf_ctx.mbx_dmabuf = dmabuf;

	if (ext_buf_cnt == 1) {
		/* bsg tracking structure */
		dd_data = kmalloc(sizeof(struct bsg_job_data), GFP_KERNEL);
		if (!dd_data) {
			rc = -ENOMEM;
			goto job_error;
		}

		/* mailbox command structure for base driver */
		pmboxq = mempool_alloc(phba->mbox_mem_pool, GFP_KERNEL);
		if (!pmboxq) {
			rc = -ENOMEM;
			goto job_error;
		}
		memset(pmboxq, 0, sizeof(LPFC_MBOXQ_t));
		pmb = &pmboxq->u.mb;
		mbx = (uint8_t *)dmabuf->virt;
		memcpy(pmb, mbx, sizeof(*pmb));
		pmb->mbxOwner = OWN_HOST;
		pmboxq->vport = phba->pport;

		/* callback for multi-buffer read mailbox command */
		pmboxq->mbox_cmpl = lpfc_bsg_issue_write_mbox_ext_cmpl;

		/* context fields to callback function */
		pmboxq->context1 = dd_data;
		dd_data->type = TYPE_MBOX;
		dd_data->set_job = job;
		dd_data->context_un.mbox.pmboxq = pmboxq;
		dd_data->context_un.mbox.mb = (MAILBOX_t *)mbx;
		job->dd_data = dd_data;

		/* state change */

		phba->mbox_ext_buf_ctx.state = LPFC_BSG_MBOX_PORT;
		rc = lpfc_sli_issue_mbox(phba, pmboxq, MBX_NOWAIT);
		if ((rc == MBX_SUCCESS) || (rc == MBX_BUSY)) {
			lpfc_printf_log(phba, KERN_INFO, LOG_LIBDFC,
					"2955 Issued SLI_CONFIG ext-buffer "
					"maibox command, rc:x%x\n", rc);
			return SLI_CONFIG_HANDLED;
		}
		lpfc_printf_log(phba, KERN_ERR, LOG_LIBDFC,
				"2956 Failed to issue SLI_CONFIG ext-buffer "
				"maibox command, rc:x%x\n", rc);
		rc = -EPIPE;
		goto job_error;
	}

	/* wait for additoinal external buffers */

	job->reply->result = 0;
	job->job_done(job);
	return SLI_CONFIG_HANDLED;

job_error:
	if (pmboxq)
		mempool_free(pmboxq, phba->mbox_mem_pool);
	kfree(dd_data);

	return rc;
}