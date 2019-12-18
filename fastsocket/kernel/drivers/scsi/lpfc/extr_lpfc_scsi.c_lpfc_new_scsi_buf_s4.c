#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint16_t ;
struct sli4_sge {int word2; void* sge_len; void* addr_lo; void* addr_hi; } ;
struct lpfc_vport {struct lpfc_hba* phba; } ;
struct TYPE_8__ {int bdeSize; int addrLow; int addrHigh; int /*<<< orphan*/  bdeFlags; scalar_t__ ulpIoTag32; } ;
struct TYPE_9__ {TYPE_2__ bdl; } ;
struct TYPE_10__ {TYPE_3__ fcpi64; } ;
struct TYPE_11__ {int ulpBdeCount; int ulpLe; int /*<<< orphan*/  ulpClass; TYPE_4__ un; } ;
struct TYPE_12__ {struct lpfc_scsi_buf* context1; TYPE_5__ iocb; int /*<<< orphan*/  iocb_flag; int /*<<< orphan*/  sli4_xritag; scalar_t__ sli4_lxritag; } ;
struct lpfc_scsi_buf {int /*<<< orphan*/  list; scalar_t__ dma_phys_bpl; TYPE_6__ cur_iocbq; scalar_t__ dma_handle; scalar_t__ fcp_bpl; scalar_t__ fcp_cmnd; struct fcp_rsp* fcp_rsp; scalar_t__ data; } ;
struct TYPE_7__ {int /*<<< orphan*/  scsi_xri_cnt; int /*<<< orphan*/ * xri_ids; } ;
struct lpfc_hba {int cfg_sg_dma_buf_size; int /*<<< orphan*/  scsi_buf_list_get_lock; TYPE_1__ sli4_hba; int /*<<< orphan*/  lpfc_scsi_dma_buf_pool; scalar_t__ cfg_enable_bg; } ;
struct fcp_rsp {int dummy; } ;
struct fcp_cmnd {int dummy; } ;
typedef  scalar_t__ dma_addr_t ;
typedef  TYPE_5__ IOCB_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUFF_TYPE_BDE_64 ; 
 int /*<<< orphan*/  CLASS3 ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOG_BG ; 
 int /*<<< orphan*/  LOG_FCP ; 
 int /*<<< orphan*/  LPFC_IO_FCP ; 
 scalar_t__ NO_XRI ; 
 int SLI4_PAGE_SIZE ; 
 int /*<<< orphan*/  bf_set (int /*<<< orphan*/ ,struct sli4_sge*,int) ; 
 void* cpu_to_le32 (int) ; 
 int /*<<< orphan*/  kfree (struct lpfc_scsi_buf*) ; 
 struct lpfc_scsi_buf* kzalloc (int,int /*<<< orphan*/ ) ; 
 void* le32_to_cpu (int) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lpfc_printf_log (struct lpfc_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  lpfc_printf_vlog (struct lpfc_vport*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int,int,int,int) ; 
 scalar_t__ lpfc_sli4_next_xritag (struct lpfc_hba*) ; 
 int lpfc_sli4_post_scsi_sgl_list (struct lpfc_hba*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lpfc_sli4_sge_last ; 
 scalar_t__ lpfc_sli_next_iotag (struct lpfc_hba*,TYPE_6__*) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,int) ; 
 scalar_t__ pci_pool_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  pci_pool_free (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  post_sblist ; 
 int /*<<< orphan*/  prep_sblist ; 
 int putPaddrHigh (scalar_t__) ; 
 int putPaddrLow (scalar_t__) ; 
 int /*<<< orphan*/  scsi_sblist ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
lpfc_new_scsi_buf_s4(struct lpfc_vport *vport, int num_to_alloc)
{
	struct lpfc_hba *phba = vport->phba;
	struct lpfc_scsi_buf *psb;
	struct sli4_sge *sgl;
	IOCB_t *iocb;
	dma_addr_t pdma_phys_fcp_cmd;
	dma_addr_t pdma_phys_fcp_rsp;
	dma_addr_t pdma_phys_bpl;
	uint16_t iotag, lxri = 0;
	int bcnt, num_posted, sgl_size;
	LIST_HEAD(prep_sblist);
	LIST_HEAD(post_sblist);
	LIST_HEAD(scsi_sblist);

	sgl_size = phba->cfg_sg_dma_buf_size -
		(sizeof(struct fcp_cmnd) + sizeof(struct fcp_rsp));

	lpfc_printf_vlog(vport, KERN_INFO, LOG_FCP,
			 "9068 ALLOC %d scsi_bufs: %d (%d + %d + %d)\n",
			 num_to_alloc, phba->cfg_sg_dma_buf_size, sgl_size,
			 (int)sizeof(struct fcp_cmnd),
			 (int)sizeof(struct fcp_rsp));

	for (bcnt = 0; bcnt < num_to_alloc; bcnt++) {
		psb = kzalloc(sizeof(struct lpfc_scsi_buf), GFP_KERNEL);
		if (!psb)
			break;
		/*
		 * Get memory from the pci pool to map the virt space to
		 * pci bus space for an I/O. The DMA buffer includes space
		 * for the struct fcp_cmnd, struct fcp_rsp and the number
		 * of bde's necessary to support the sg_tablesize.
		 */
		psb->data = pci_pool_alloc(phba->lpfc_scsi_dma_buf_pool,
						GFP_KERNEL, &psb->dma_handle);
		if (!psb->data) {
			kfree(psb);
			break;
		}
		memset(psb->data, 0, phba->cfg_sg_dma_buf_size);

		/*
		 * 4K Page alignment is CRITICAL to BlockGuard, double check
		 * to be sure.
		 */
		if (phba->cfg_enable_bg  && (((unsigned long)(psb->data) &
		    (unsigned long)(SLI4_PAGE_SIZE - 1)) != 0)) {
			pci_pool_free(phba->lpfc_scsi_dma_buf_pool,
				      psb->data, psb->dma_handle);
			kfree(psb);
			break;
		}

		/* Allocate iotag for psb->cur_iocbq. */
		iotag = lpfc_sli_next_iotag(phba, &psb->cur_iocbq);
		if (iotag == 0) {
			pci_pool_free(phba->lpfc_scsi_dma_buf_pool,
				psb->data, psb->dma_handle);
			kfree(psb);
			break;
		}

		lxri = lpfc_sli4_next_xritag(phba);
		if (lxri == NO_XRI) {
			pci_pool_free(phba->lpfc_scsi_dma_buf_pool,
			      psb->data, psb->dma_handle);
			kfree(psb);
			break;
		}
		psb->cur_iocbq.sli4_lxritag = lxri;
		psb->cur_iocbq.sli4_xritag = phba->sli4_hba.xri_ids[lxri];
		psb->cur_iocbq.iocb_flag |= LPFC_IO_FCP;
		psb->fcp_bpl = psb->data;
		psb->fcp_cmnd = (psb->data + sgl_size);
		psb->fcp_rsp = (struct fcp_rsp *)((uint8_t *)psb->fcp_cmnd +
					sizeof(struct fcp_cmnd));

		/* Initialize local short-hand pointers. */
		sgl = (struct sli4_sge *)psb->fcp_bpl;
		pdma_phys_bpl = psb->dma_handle;
		pdma_phys_fcp_cmd = (psb->dma_handle + sgl_size);
		pdma_phys_fcp_rsp = pdma_phys_fcp_cmd + sizeof(struct fcp_cmnd);

		/*
		 * The first two bdes are the FCP_CMD and FCP_RSP.
		 * The balance are sg list bdes. Initialize the
		 * first two and leave the rest for queuecommand.
		 */
		sgl->addr_hi = cpu_to_le32(putPaddrHigh(pdma_phys_fcp_cmd));
		sgl->addr_lo = cpu_to_le32(putPaddrLow(pdma_phys_fcp_cmd));
		sgl->word2 = le32_to_cpu(sgl->word2);
		bf_set(lpfc_sli4_sge_last, sgl, 0);
		sgl->word2 = cpu_to_le32(sgl->word2);
		sgl->sge_len = cpu_to_le32(sizeof(struct fcp_cmnd));
		sgl++;

		/* Setup the physical region for the FCP RSP */
		sgl->addr_hi = cpu_to_le32(putPaddrHigh(pdma_phys_fcp_rsp));
		sgl->addr_lo = cpu_to_le32(putPaddrLow(pdma_phys_fcp_rsp));
		sgl->word2 = le32_to_cpu(sgl->word2);
		bf_set(lpfc_sli4_sge_last, sgl, 1);
		sgl->word2 = cpu_to_le32(sgl->word2);
		sgl->sge_len = cpu_to_le32(sizeof(struct fcp_rsp));

		/*
		 * Since the IOCB for the FCP I/O is built into this
		 * lpfc_scsi_buf, initialize it with all known data now.
		 */
		iocb = &psb->cur_iocbq.iocb;
		iocb->un.fcpi64.bdl.ulpIoTag32 = 0;
		iocb->un.fcpi64.bdl.bdeFlags = BUFF_TYPE_BDE_64;
		/* setting the BLP size to 2 * sizeof BDE may not be correct.
		 * We are setting the bpl to point to out sgl. An sgl's
		 * entries are 16 bytes, a bpl entries are 12 bytes.
		 */
		iocb->un.fcpi64.bdl.bdeSize = sizeof(struct fcp_cmnd);
		iocb->un.fcpi64.bdl.addrLow = putPaddrLow(pdma_phys_fcp_cmd);
		iocb->un.fcpi64.bdl.addrHigh = putPaddrHigh(pdma_phys_fcp_cmd);
		iocb->ulpBdeCount = 1;
		iocb->ulpLe = 1;
		iocb->ulpClass = CLASS3;
		psb->cur_iocbq.context1 = psb;
		psb->dma_phys_bpl = pdma_phys_bpl;

		/* add the scsi buffer to a post list */
		list_add_tail(&psb->list, &post_sblist);
		spin_lock_irq(&phba->scsi_buf_list_get_lock);
		phba->sli4_hba.scsi_xri_cnt++;
		spin_unlock_irq(&phba->scsi_buf_list_get_lock);
	}
	lpfc_printf_log(phba, KERN_INFO, LOG_BG,
			"3021 Allocate %d out of %d requested new SCSI "
			"buffers\n", bcnt, num_to_alloc);

	/* post the list of scsi buffer sgls to port if available */
	if (!list_empty(&post_sblist))
		num_posted = lpfc_sli4_post_scsi_sgl_list(phba,
							  &post_sblist, bcnt);
	else
		num_posted = 0;

	return num_posted;
}