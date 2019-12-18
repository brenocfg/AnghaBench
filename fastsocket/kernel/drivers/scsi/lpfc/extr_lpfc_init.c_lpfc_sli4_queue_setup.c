#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_45__   TYPE_9__ ;
typedef  struct TYPE_44__   TYPE_8__ ;
typedef  struct TYPE_43__   TYPE_7__ ;
typedef  struct TYPE_42__   TYPE_6__ ;
typedef  struct TYPE_41__   TYPE_5__ ;
typedef  struct TYPE_40__   TYPE_4__ ;
typedef  struct TYPE_39__   TYPE_3__ ;
typedef  struct TYPE_38__   TYPE_2__ ;
typedef  struct TYPE_37__   TYPE_25__ ;
typedef  struct TYPE_36__   TYPE_22__ ;
typedef  struct TYPE_35__   TYPE_1__ ;
typedef  struct TYPE_34__   TYPE_18__ ;
typedef  struct TYPE_33__   TYPE_15__ ;
typedef  struct TYPE_32__   TYPE_13__ ;
typedef  struct TYPE_31__   TYPE_11__ ;
typedef  struct TYPE_30__   TYPE_10__ ;

/* Type definitions */
union lpfc_sli4_cfg_shdr {int /*<<< orphan*/  response; } ;
typedef  int uint32_t ;
struct TYPE_44__ {void* wqp; } ;
struct TYPE_45__ {TYPE_8__ sli4; } ;
struct lpfc_sli_ring {TYPE_9__ sli; } ;
struct lpfc_sli4_cfg_mhdr {int dummy; } ;
struct lpfc_sli {struct lpfc_sli_ring* ring; } ;
struct lpfc_mbx_query_fw_config {int dummy; } ;
struct TYPE_30__ {int fw_func_mode; int ulp0_mode; int ulp1_mode; int* fcp_cq_map; TYPE_25__** hba_eq; TYPE_15__** fcp_cq; TYPE_13__** fcp_wq; TYPE_15__* mbx_cq; TYPE_15__* els_cq; TYPE_22__* mbx_wq; TYPE_13__* els_wq; TYPE_18__* dat_rq; TYPE_18__* hdr_rq; } ;
struct lpfc_hba {int cfg_fcp_io_channel; int cfg_fcp_imax; TYPE_10__ sli4_hba; int /*<<< orphan*/  mbox_mem_pool; struct lpfc_sli sli; } ;
struct TYPE_39__ {int function_mode; int ulp0_mode; int ulp1_mode; } ;
struct TYPE_40__ {TYPE_3__ rsp; } ;
struct TYPE_35__ {int /*<<< orphan*/  cfg_shdr; } ;
struct TYPE_38__ {TYPE_1__ header; } ;
struct TYPE_41__ {TYPE_4__ query_fw_cfg; TYPE_2__ sli4_config; } ;
struct TYPE_42__ {TYPE_5__ un; } ;
struct TYPE_43__ {TYPE_6__ mqe; } ;
struct TYPE_37__ {int /*<<< orphan*/  queue_id; } ;
struct TYPE_36__ {int /*<<< orphan*/  queue_id; } ;
struct TYPE_34__ {int queue_id; } ;
struct TYPE_33__ {int queue_id; struct lpfc_sli_ring* pring; } ;
struct TYPE_32__ {int /*<<< orphan*/  queue_id; } ;
struct TYPE_31__ {TYPE_7__ u; } ;
typedef  TYPE_11__ LPFC_MBOXQ_t ;

/* Variables and functions */
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  LOG_INIT ; 
 int /*<<< orphan*/  LPFC_ELS ; 
 int /*<<< orphan*/  LPFC_ELS_HBQ ; 
 size_t LPFC_ELS_RING ; 
 int /*<<< orphan*/  LPFC_FCP ; 
 int /*<<< orphan*/  LPFC_MBOX ; 
 int /*<<< orphan*/  LPFC_MBOX_OPCODE_QUERY_FW_CFG ; 
 int /*<<< orphan*/  LPFC_MBOX_SUBSYSTEM_COMMON ; 
 int /*<<< orphan*/  LPFC_MCQ ; 
 int /*<<< orphan*/  LPFC_SLI4_MBX_EMBED ; 
 int /*<<< orphan*/  LPFC_USOL ; 
 int /*<<< orphan*/  LPFC_WCQ ; 
 int MAX_SLI3_CONFIGURED_RINGS ; 
 int /*<<< orphan*/  MBX_POLL ; 
 int MBX_TIMEOUT ; 
 int bf_get (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int lpfc_cq_create (struct lpfc_hba*,TYPE_15__*,TYPE_25__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_cq_destroy (struct lpfc_hba*,TYPE_15__*) ; 
 int lpfc_eq_create (struct lpfc_hba*,TYPE_25__*,int) ; 
 int /*<<< orphan*/  lpfc_eq_destroy (struct lpfc_hba*,TYPE_25__*) ; 
 int /*<<< orphan*/  lpfc_mbox_hdr_add_status ; 
 int /*<<< orphan*/  lpfc_mbox_hdr_status ; 
 int lpfc_mq_create (struct lpfc_hba*,TYPE_22__*,TYPE_15__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_mq_destroy (struct lpfc_hba*,TYPE_22__*) ; 
 int /*<<< orphan*/  lpfc_printf_log (struct lpfc_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  lpfc_rq_adjust_repost (struct lpfc_hba*,TYPE_18__*,int /*<<< orphan*/ ) ; 
 int lpfc_rq_create (struct lpfc_hba*,TYPE_18__*,TYPE_18__*,TYPE_15__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_sli4_config (struct lpfc_hba*,TYPE_11__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int lpfc_sli_issue_mbox (struct lpfc_hba*,TYPE_11__*,int /*<<< orphan*/ ) ; 
 int lpfc_wq_create (struct lpfc_hba*,TYPE_13__*,TYPE_15__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_wq_destroy (struct lpfc_hba*,TYPE_13__*) ; 
 scalar_t__ mempool_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mempool_free (TYPE_11__*,int /*<<< orphan*/ ) ; 

int
lpfc_sli4_queue_setup(struct lpfc_hba *phba)
{
	struct lpfc_sli *psli = &phba->sli;
	struct lpfc_sli_ring *pring;
	int rc = -ENOMEM;
	int fcp_eqidx, fcp_cqidx, fcp_wqidx;
	int fcp_cq_index = 0;
	uint32_t shdr_status, shdr_add_status;
	union lpfc_sli4_cfg_shdr *shdr;
	LPFC_MBOXQ_t *mboxq;
	uint32_t length;

	/* Check for dual-ULP support */
	mboxq = (LPFC_MBOXQ_t *)mempool_alloc(phba->mbox_mem_pool, GFP_KERNEL);
	if (!mboxq) {
		lpfc_printf_log(phba, KERN_ERR, LOG_INIT,
				"3249 Unable to allocate memory for "
				"QUERY_FW_CFG mailbox command\n");
		return -ENOMEM;
	}
	length = (sizeof(struct lpfc_mbx_query_fw_config) -
		  sizeof(struct lpfc_sli4_cfg_mhdr));
	lpfc_sli4_config(phba, mboxq, LPFC_MBOX_SUBSYSTEM_COMMON,
			 LPFC_MBOX_OPCODE_QUERY_FW_CFG,
			 length, LPFC_SLI4_MBX_EMBED);

	rc = lpfc_sli_issue_mbox(phba, mboxq, MBX_POLL);

	shdr = (union lpfc_sli4_cfg_shdr *)
			&mboxq->u.mqe.un.sli4_config.header.cfg_shdr;
	shdr_status = bf_get(lpfc_mbox_hdr_status, &shdr->response);
	shdr_add_status = bf_get(lpfc_mbox_hdr_add_status, &shdr->response);
	if (shdr_status || shdr_add_status || rc) {
		lpfc_printf_log(phba, KERN_ERR, LOG_INIT,
				"3250 QUERY_FW_CFG mailbox failed with status "
				"x%x add_status x%x, mbx status x%x\n",
				shdr_status, shdr_add_status, rc);
		if (rc != MBX_TIMEOUT)
			mempool_free(mboxq, phba->mbox_mem_pool);
		rc = -ENXIO;
		goto out_error;
	}

	phba->sli4_hba.fw_func_mode =
			mboxq->u.mqe.un.query_fw_cfg.rsp.function_mode;
	phba->sli4_hba.ulp0_mode = mboxq->u.mqe.un.query_fw_cfg.rsp.ulp0_mode;
	phba->sli4_hba.ulp1_mode = mboxq->u.mqe.un.query_fw_cfg.rsp.ulp1_mode;
	lpfc_printf_log(phba, KERN_INFO, LOG_INIT,
			"3251 QUERY_FW_CFG: func_mode:x%x, ulp0_mode:x%x, "
			"ulp1_mode:x%x\n", phba->sli4_hba.fw_func_mode,
			phba->sli4_hba.ulp0_mode, phba->sli4_hba.ulp1_mode);

	if (rc != MBX_TIMEOUT)
		mempool_free(mboxq, phba->mbox_mem_pool);

	/*
	 * Set up HBA Event Queues (EQs)
	 */

	/* Set up HBA event queue */
	if (phba->cfg_fcp_io_channel && !phba->sli4_hba.hba_eq) {
		lpfc_printf_log(phba, KERN_ERR, LOG_INIT,
				"3147 Fast-path EQs not allocated\n");
		rc = -ENOMEM;
		goto out_error;
	}
	for (fcp_eqidx = 0; fcp_eqidx < phba->cfg_fcp_io_channel; fcp_eqidx++) {
		if (!phba->sli4_hba.hba_eq[fcp_eqidx]) {
			lpfc_printf_log(phba, KERN_ERR, LOG_INIT,
					"0522 Fast-path EQ (%d) not "
					"allocated\n", fcp_eqidx);
			rc = -ENOMEM;
			goto out_destroy_hba_eq;
		}
		rc = lpfc_eq_create(phba, phba->sli4_hba.hba_eq[fcp_eqidx],
			 (phba->cfg_fcp_imax / phba->cfg_fcp_io_channel));
		if (rc) {
			lpfc_printf_log(phba, KERN_ERR, LOG_INIT,
					"0523 Failed setup of fast-path EQ "
					"(%d), rc = 0x%x\n", fcp_eqidx, rc);
			goto out_destroy_hba_eq;
		}
		lpfc_printf_log(phba, KERN_INFO, LOG_INIT,
				"2584 HBA EQ setup: "
				"queue[%d]-id=%d\n", fcp_eqidx,
				phba->sli4_hba.hba_eq[fcp_eqidx]->queue_id);
	}

	/* Set up fast-path FCP Response Complete Queue */
	if (!phba->sli4_hba.fcp_cq) {
		lpfc_printf_log(phba, KERN_ERR, LOG_INIT,
				"3148 Fast-path FCP CQ array not "
				"allocated\n");
		rc = -ENOMEM;
		goto out_destroy_hba_eq;
	}

	for (fcp_cqidx = 0; fcp_cqidx < phba->cfg_fcp_io_channel; fcp_cqidx++) {
		if (!phba->sli4_hba.fcp_cq[fcp_cqidx]) {
			lpfc_printf_log(phba, KERN_ERR, LOG_INIT,
					"0526 Fast-path FCP CQ (%d) not "
					"allocated\n", fcp_cqidx);
			rc = -ENOMEM;
			goto out_destroy_fcp_cq;
		}
		rc = lpfc_cq_create(phba, phba->sli4_hba.fcp_cq[fcp_cqidx],
			phba->sli4_hba.hba_eq[fcp_cqidx], LPFC_WCQ, LPFC_FCP);
		if (rc) {
			lpfc_printf_log(phba, KERN_ERR, LOG_INIT,
					"0527 Failed setup of fast-path FCP "
					"CQ (%d), rc = 0x%x\n", fcp_cqidx, rc);
			goto out_destroy_fcp_cq;
		}

		/* Setup fcp_cq_map for fast lookup */
		phba->sli4_hba.fcp_cq_map[fcp_cqidx] =
				phba->sli4_hba.fcp_cq[fcp_cqidx]->queue_id;

		lpfc_printf_log(phba, KERN_INFO, LOG_INIT,
				"2588 FCP CQ setup: cq[%d]-id=%d, "
				"parent seq[%d]-id=%d\n",
				fcp_cqidx,
				phba->sli4_hba.fcp_cq[fcp_cqidx]->queue_id,
				fcp_cqidx,
				phba->sli4_hba.hba_eq[fcp_cqidx]->queue_id);
	}

	/* Set up fast-path FCP Work Queue */
	if (!phba->sli4_hba.fcp_wq) {
		lpfc_printf_log(phba, KERN_ERR, LOG_INIT,
				"3149 Fast-path FCP WQ array not "
				"allocated\n");
		rc = -ENOMEM;
		goto out_destroy_fcp_cq;
	}

	for (fcp_wqidx = 0; fcp_wqidx < phba->cfg_fcp_io_channel; fcp_wqidx++) {
		if (!phba->sli4_hba.fcp_wq[fcp_wqidx]) {
			lpfc_printf_log(phba, KERN_ERR, LOG_INIT,
					"0534 Fast-path FCP WQ (%d) not "
					"allocated\n", fcp_wqidx);
			rc = -ENOMEM;
			goto out_destroy_fcp_wq;
		}
		rc = lpfc_wq_create(phba, phba->sli4_hba.fcp_wq[fcp_wqidx],
				    phba->sli4_hba.fcp_cq[fcp_wqidx],
				    LPFC_FCP);
		if (rc) {
			lpfc_printf_log(phba, KERN_ERR, LOG_INIT,
					"0535 Failed setup of fast-path FCP "
					"WQ (%d), rc = 0x%x\n", fcp_wqidx, rc);
			goto out_destroy_fcp_wq;
		}

		/* Bind this WQ to the next FCP ring */
		pring = &psli->ring[MAX_SLI3_CONFIGURED_RINGS + fcp_wqidx];
		pring->sli.sli4.wqp = (void *)phba->sli4_hba.fcp_wq[fcp_wqidx];
		phba->sli4_hba.fcp_cq[fcp_wqidx]->pring = pring;

		lpfc_printf_log(phba, KERN_INFO, LOG_INIT,
				"2591 FCP WQ setup: wq[%d]-id=%d, "
				"parent cq[%d]-id=%d\n",
				fcp_wqidx,
				phba->sli4_hba.fcp_wq[fcp_wqidx]->queue_id,
				fcp_cq_index,
				phba->sli4_hba.fcp_cq[fcp_wqidx]->queue_id);
	}
	/*
	 * Set up Complete Queues (CQs)
	 */

	/* Set up slow-path MBOX Complete Queue as the first CQ */
	if (!phba->sli4_hba.mbx_cq) {
		lpfc_printf_log(phba, KERN_ERR, LOG_INIT,
				"0528 Mailbox CQ not allocated\n");
		rc = -ENOMEM;
		goto out_destroy_fcp_wq;
	}
	rc = lpfc_cq_create(phba, phba->sli4_hba.mbx_cq,
			phba->sli4_hba.hba_eq[0], LPFC_MCQ, LPFC_MBOX);
	if (rc) {
		lpfc_printf_log(phba, KERN_ERR, LOG_INIT,
				"0529 Failed setup of slow-path mailbox CQ: "
				"rc = 0x%x\n", rc);
		goto out_destroy_fcp_wq;
	}
	lpfc_printf_log(phba, KERN_INFO, LOG_INIT,
			"2585 MBX CQ setup: cq-id=%d, parent eq-id=%d\n",
			phba->sli4_hba.mbx_cq->queue_id,
			phba->sli4_hba.hba_eq[0]->queue_id);

	/* Set up slow-path ELS Complete Queue */
	if (!phba->sli4_hba.els_cq) {
		lpfc_printf_log(phba, KERN_ERR, LOG_INIT,
				"0530 ELS CQ not allocated\n");
		rc = -ENOMEM;
		goto out_destroy_mbx_cq;
	}
	rc = lpfc_cq_create(phba, phba->sli4_hba.els_cq,
			phba->sli4_hba.hba_eq[0], LPFC_WCQ, LPFC_ELS);
	if (rc) {
		lpfc_printf_log(phba, KERN_ERR, LOG_INIT,
				"0531 Failed setup of slow-path ELS CQ: "
				"rc = 0x%x\n", rc);
		goto out_destroy_mbx_cq;
	}
	lpfc_printf_log(phba, KERN_INFO, LOG_INIT,
			"2586 ELS CQ setup: cq-id=%d, parent eq-id=%d\n",
			phba->sli4_hba.els_cq->queue_id,
			phba->sli4_hba.hba_eq[0]->queue_id);

	/*
	 * Set up all the Work Queues (WQs)
	 */

	/* Set up Mailbox Command Queue */
	if (!phba->sli4_hba.mbx_wq) {
		lpfc_printf_log(phba, KERN_ERR, LOG_INIT,
				"0538 Slow-path MQ not allocated\n");
		rc = -ENOMEM;
		goto out_destroy_els_cq;
	}
	rc = lpfc_mq_create(phba, phba->sli4_hba.mbx_wq,
			    phba->sli4_hba.mbx_cq, LPFC_MBOX);
	if (rc) {
		lpfc_printf_log(phba, KERN_ERR, LOG_INIT,
				"0539 Failed setup of slow-path MQ: "
				"rc = 0x%x\n", rc);
		goto out_destroy_els_cq;
	}
	lpfc_printf_log(phba, KERN_INFO, LOG_INIT,
			"2589 MBX MQ setup: wq-id=%d, parent cq-id=%d\n",
			phba->sli4_hba.mbx_wq->queue_id,
			phba->sli4_hba.mbx_cq->queue_id);

	/* Set up slow-path ELS Work Queue */
	if (!phba->sli4_hba.els_wq) {
		lpfc_printf_log(phba, KERN_ERR, LOG_INIT,
				"0536 Slow-path ELS WQ not allocated\n");
		rc = -ENOMEM;
		goto out_destroy_mbx_wq;
	}
	rc = lpfc_wq_create(phba, phba->sli4_hba.els_wq,
			    phba->sli4_hba.els_cq, LPFC_ELS);
	if (rc) {
		lpfc_printf_log(phba, KERN_ERR, LOG_INIT,
				"0537 Failed setup of slow-path ELS WQ: "
				"rc = 0x%x\n", rc);
		goto out_destroy_mbx_wq;
	}

	/* Bind this WQ to the ELS ring */
	pring = &psli->ring[LPFC_ELS_RING];
	pring->sli.sli4.wqp = (void *)phba->sli4_hba.els_wq;
	phba->sli4_hba.els_cq->pring = pring;

	lpfc_printf_log(phba, KERN_INFO, LOG_INIT,
			"2590 ELS WQ setup: wq-id=%d, parent cq-id=%d\n",
			phba->sli4_hba.els_wq->queue_id,
			phba->sli4_hba.els_cq->queue_id);

	/*
	 * Create Receive Queue (RQ)
	 */
	if (!phba->sli4_hba.hdr_rq || !phba->sli4_hba.dat_rq) {
		lpfc_printf_log(phba, KERN_ERR, LOG_INIT,
				"0540 Receive Queue not allocated\n");
		rc = -ENOMEM;
		goto out_destroy_els_wq;
	}

	lpfc_rq_adjust_repost(phba, phba->sli4_hba.hdr_rq, LPFC_ELS_HBQ);
	lpfc_rq_adjust_repost(phba, phba->sli4_hba.dat_rq, LPFC_ELS_HBQ);

	rc = lpfc_rq_create(phba, phba->sli4_hba.hdr_rq, phba->sli4_hba.dat_rq,
			    phba->sli4_hba.els_cq, LPFC_USOL);
	if (rc) {
		lpfc_printf_log(phba, KERN_ERR, LOG_INIT,
				"0541 Failed setup of Receive Queue: "
				"rc = 0x%x\n", rc);
		goto out_destroy_fcp_wq;
	}

	lpfc_printf_log(phba, KERN_INFO, LOG_INIT,
			"2592 USL RQ setup: hdr-rq-id=%d, dat-rq-id=%d "
			"parent cq-id=%d\n",
			phba->sli4_hba.hdr_rq->queue_id,
			phba->sli4_hba.dat_rq->queue_id,
			phba->sli4_hba.els_cq->queue_id);
	return 0;

out_destroy_els_wq:
	lpfc_wq_destroy(phba, phba->sli4_hba.els_wq);
out_destroy_mbx_wq:
	lpfc_mq_destroy(phba, phba->sli4_hba.mbx_wq);
out_destroy_els_cq:
	lpfc_cq_destroy(phba, phba->sli4_hba.els_cq);
out_destroy_mbx_cq:
	lpfc_cq_destroy(phba, phba->sli4_hba.mbx_cq);
out_destroy_fcp_wq:
	for (--fcp_wqidx; fcp_wqidx >= 0; fcp_wqidx--)
		lpfc_wq_destroy(phba, phba->sli4_hba.fcp_wq[fcp_wqidx]);
out_destroy_fcp_cq:
	for (--fcp_cqidx; fcp_cqidx >= 0; fcp_cqidx--)
		lpfc_cq_destroy(phba, phba->sli4_hba.fcp_cq[fcp_cqidx]);
out_destroy_hba_eq:
	for (--fcp_eqidx; fcp_eqidx >= 0; fcp_eqidx--)
		lpfc_eq_destroy(phba, phba->sli4_hba.hba_eq[fcp_eqidx]);
out_error:
	return rc;
}