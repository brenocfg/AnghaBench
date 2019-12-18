#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct sli4_sge {int /*<<< orphan*/  word2; } ;
struct scsi_cmnd {int sc_data_direction; } ;
struct TYPE_7__ {int fcpi_parm; } ;
struct TYPE_8__ {TYPE_2__ fcpi; } ;
struct TYPE_10__ {TYPE_3__ un; } ;
struct TYPE_6__ {int /*<<< orphan*/  iocb_flag; TYPE_5__ iocb; } ;
struct lpfc_scsi_buf {int seg_cnt; int prot_seg_cnt; TYPE_1__ cur_iocbq; scalar_t__ fcp_bpl; struct fcp_cmnd* fcp_cmnd; struct scsi_cmnd* pCmd; } ;
struct lpfc_hba {int cfg_sg_seg_cnt; int cfg_total_seg_cnt; TYPE_4__* pcidev; } ;
struct fcp_cmnd {int /*<<< orphan*/  fcpDl; } ;
struct TYPE_9__ {int /*<<< orphan*/  dev; } ;
typedef  TYPE_5__ IOCB_t ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  LOG_FCP ; 
 int /*<<< orphan*/  LPFC_IO_DIF_INSERT ; 
 int /*<<< orphan*/  LPFC_IO_DIF_PASS ; 
 int /*<<< orphan*/  LPFC_IO_DIF_STRIP ; 
#define  LPFC_PG_TYPE_DIF_BUF 136 
#define  LPFC_PG_TYPE_INVALID 135 
#define  LPFC_PG_TYPE_NO_DIF 134 
#define  SCSI_PROT_READ_INSERT 133 
#define  SCSI_PROT_READ_PASS 132 
#define  SCSI_PROT_READ_STRIP 131 
#define  SCSI_PROT_WRITE_INSERT 130 
#define  SCSI_PROT_WRITE_PASS 129 
#define  SCSI_PROT_WRITE_STRIP 128 
 int /*<<< orphan*/  be32_to_cpu (int) ; 
 int /*<<< orphan*/  bf_set (int /*<<< orphan*/ ,struct sli4_sge*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int dma_map_sg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  dma_unmap_sg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int lpfc_bg_scsi_adjust_dl (struct lpfc_hba*,struct lpfc_scsi_buf*) ; 
 int lpfc_bg_setup_sgl (struct lpfc_hba*,struct scsi_cmnd*,struct sli4_sge*,int) ; 
 int lpfc_bg_setup_sgl_prot (struct lpfc_hba*,struct scsi_cmnd*,struct sli4_sge*,int,int) ; 
 int /*<<< orphan*/  lpfc_printf_log (struct lpfc_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,...) ; 
 int lpfc_prot_group_type (struct lpfc_hba*,struct scsi_cmnd*) ; 
 int /*<<< orphan*/  lpfc_sli4_sge_last ; 
 int /*<<< orphan*/  scsi_dma_unmap (struct scsi_cmnd*) ; 
 int scsi_get_prot_op (struct scsi_cmnd*) ; 
 scalar_t__ scsi_prot_sg_count (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  scsi_prot_sglist (struct scsi_cmnd*) ; 
 scalar_t__ scsi_sg_count (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  scsi_sglist (struct scsi_cmnd*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int
lpfc_bg_scsi_prep_dma_buf_s4(struct lpfc_hba *phba,
		struct lpfc_scsi_buf *lpfc_cmd)
{
	struct scsi_cmnd *scsi_cmnd = lpfc_cmd->pCmd;
	struct fcp_cmnd *fcp_cmnd = lpfc_cmd->fcp_cmnd;
	struct sli4_sge *sgl = (struct sli4_sge *)(lpfc_cmd->fcp_bpl);
	IOCB_t *iocb_cmd = &lpfc_cmd->cur_iocbq.iocb;
	uint32_t num_sge = 0;
	int datasegcnt, protsegcnt, datadir = scsi_cmnd->sc_data_direction;
	int prot_group_type = 0;
	int fcpdl;

	/*
	 * Start the lpfc command prep by bumping the sgl beyond fcp_cmnd
	 *  fcp_rsp regions to the first data sge entry
	 */
	if (scsi_sg_count(scsi_cmnd)) {
		/*
		 * The driver stores the segment count returned from pci_map_sg
		 * because this a count of dma-mappings used to map the use_sg
		 * pages.  They are not guaranteed to be the same for those
		 * architectures that implement an IOMMU.
		 */
		datasegcnt = dma_map_sg(&phba->pcidev->dev,
					scsi_sglist(scsi_cmnd),
					scsi_sg_count(scsi_cmnd), datadir);
		if (unlikely(!datasegcnt))
			return 1;

		sgl += 1;
		/* clear the last flag in the fcp_rsp map entry */
		sgl->word2 = le32_to_cpu(sgl->word2);
		bf_set(lpfc_sli4_sge_last, sgl, 0);
		sgl->word2 = cpu_to_le32(sgl->word2);

		sgl += 1;
		lpfc_cmd->seg_cnt = datasegcnt;

		/* First check if data segment count from SCSI Layer is good */
		if (lpfc_cmd->seg_cnt > phba->cfg_sg_seg_cnt)
			goto err;

		prot_group_type = lpfc_prot_group_type(phba, scsi_cmnd);

		switch (prot_group_type) {
		case LPFC_PG_TYPE_NO_DIF:
			/* Here we need to add a DISEED to the count */
			if ((lpfc_cmd->seg_cnt + 1) > phba->cfg_total_seg_cnt)
				goto err;

			num_sge = lpfc_bg_setup_sgl(phba, scsi_cmnd, sgl,
					datasegcnt);

			/* we should have 2 or more entries in buffer list */
			if (num_sge < 2)
				goto err;
			break;

		case LPFC_PG_TYPE_DIF_BUF:
			/*
			 * This type indicates that protection buffers are
			 * passed to the driver, so that needs to be prepared
			 * for DMA
			 */
			protsegcnt = dma_map_sg(&phba->pcidev->dev,
					scsi_prot_sglist(scsi_cmnd),
					scsi_prot_sg_count(scsi_cmnd), datadir);
			if (unlikely(!protsegcnt)) {
				scsi_dma_unmap(scsi_cmnd);
				return 1;
			}

			lpfc_cmd->prot_seg_cnt = protsegcnt;
			/*
			 * There is a minimun of 3 SGEs used for every
			 * protection data segment.
			 */
			if ((lpfc_cmd->prot_seg_cnt * 3) >
			    (phba->cfg_total_seg_cnt - 2))
				goto err;

			num_sge = lpfc_bg_setup_sgl_prot(phba, scsi_cmnd, sgl,
					datasegcnt, protsegcnt);

			/* we should have 3 or more entries in buffer list */
			if ((num_sge < 3) ||
			    (num_sge > phba->cfg_total_seg_cnt))
				goto err;
			break;

		case LPFC_PG_TYPE_INVALID:
		default:
			scsi_dma_unmap(scsi_cmnd);
			lpfc_cmd->seg_cnt = 0;

			lpfc_printf_log(phba, KERN_ERR, LOG_FCP,
					"9083 Unexpected protection group %i\n",
					prot_group_type);
			return 1;
		}
	}

	switch (scsi_get_prot_op(scsi_cmnd)) {
	case SCSI_PROT_WRITE_STRIP:
	case SCSI_PROT_READ_STRIP:
		lpfc_cmd->cur_iocbq.iocb_flag |= LPFC_IO_DIF_STRIP;
		break;
	case SCSI_PROT_WRITE_INSERT:
	case SCSI_PROT_READ_INSERT:
		lpfc_cmd->cur_iocbq.iocb_flag |= LPFC_IO_DIF_INSERT;
		break;
	case SCSI_PROT_WRITE_PASS:
	case SCSI_PROT_READ_PASS:
		lpfc_cmd->cur_iocbq.iocb_flag |= LPFC_IO_DIF_PASS;
		break;
	}

	fcpdl = lpfc_bg_scsi_adjust_dl(phba, lpfc_cmd);
	fcp_cmnd->fcpDl = be32_to_cpu(fcpdl);

	/*
	 * Due to difference in data length between DIF/non-DIF paths,
	 * we need to set word 4 of IOCB here
	 */
	iocb_cmd->un.fcpi.fcpi_parm = fcpdl;

	return 0;
err:
	if (lpfc_cmd->seg_cnt)
		scsi_dma_unmap(scsi_cmnd);
	if (lpfc_cmd->prot_seg_cnt)
		dma_unmap_sg(&phba->pcidev->dev, scsi_prot_sglist(scsi_cmnd),
			     scsi_prot_sg_count(scsi_cmnd),
			     scsi_cmnd->sc_data_direction);

	lpfc_printf_log(phba, KERN_ERR, LOG_FCP,
			"9084 Cannot setup S/G List for HBA"
			"IO segs %d/%d SGL %d SCSI %d: %d %d\n",
			lpfc_cmd->seg_cnt, lpfc_cmd->prot_seg_cnt,
			phba->cfg_total_seg_cnt, phba->cfg_sg_seg_cnt,
			prot_group_type, num_sge);

	lpfc_cmd->seg_cnt = 0;
	lpfc_cmd->prot_seg_cnt = 0;
	return 1;
}