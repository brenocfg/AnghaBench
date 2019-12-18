#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct ulp_bde64 {int dummy; } ;
struct lpfc_sli_ring {int dummy; } ;
struct TYPE_8__ {unsigned long data; int /*<<< orphan*/  function; } ;
struct lpfc_sli {struct lpfc_sli_ring* ring; TYPE_4__ mbox_tmo; } ;
struct lpfc_hba {int work_ha_mask; int cfg_sg_seg_cnt; int cfg_sg_dma_buf_size; int cfg_total_seg_cnt; int /*<<< orphan*/  cfg_sriov_nr_virtfn; scalar_t__ max_vports; int /*<<< orphan*/  max_vpi; scalar_t__ cfg_enable_bg; struct lpfc_sli sli; int /*<<< orphan*/  menlo_flag; TYPE_1__* pcidev; TYPE_4__ eratt_poll; TYPE_4__ fabric_block_timer; TYPE_4__ fcp_poll_timer; TYPE_4__ hb_tmofunc; } ;
struct fcp_rsp {int dummy; } ;
struct fcp_cmnd {int dummy; } ;
struct TYPE_7__ {int sg_tablesize; } ;
struct TYPE_6__ {int sg_tablesize; } ;
struct TYPE_5__ {scalar_t__ device; } ;

/* Variables and functions */
 int /*<<< orphan*/  BPL_ALIGN_SZ ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HA_ERATT ; 
 int HA_LATT ; 
 int HA_MBATT ; 
 int HA_RXMASK ; 
 int /*<<< orphan*/  HBA_MENLO_SUPPORT ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  KERN_WARNING ; 
 int LOG_FCP ; 
 int LOG_INIT ; 
 int LPFC_DEFAULT_MENLO_SG_SEG_CNT ; 
 int LPFC_ELS_RING ; 
 int LPFC_MAX_SG_SEG_CNT ; 
 int LPFC_MAX_SG_SEG_CNT_DIF ; 
 int /*<<< orphan*/  LPFC_MAX_VPI ; 
 int LPFC_SLI3_MAX_RING ; 
 scalar_t__ PCI_DEVICE_ID_HORNET ; 
 int /*<<< orphan*/  init_timer (TYPE_4__*) ; 
 scalar_t__ kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_fabric_block_timeout ; 
 int /*<<< orphan*/  lpfc_get_cfgparam (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_hb_timeout ; 
 int /*<<< orphan*/  lpfc_mbox_timeout ; 
 scalar_t__ lpfc_mem_alloc (struct lpfc_hba*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_poll_eratt ; 
 int /*<<< orphan*/  lpfc_poll_timeout ; 
 int /*<<< orphan*/  lpfc_printf_log (struct lpfc_hba*,int /*<<< orphan*/ ,int,char*,int,...) ; 
 int lpfc_sli_probe_sriov_nr_virtfn (struct lpfc_hba*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_sli_queue_setup (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_sli_setup (struct lpfc_hba*) ; 
 TYPE_3__ lpfc_template ; 
 TYPE_2__ lpfc_vport_template ; 

__attribute__((used)) static int
lpfc_sli_driver_resource_setup(struct lpfc_hba *phba)
{
	struct lpfc_sli *psli;
	int rc;

	/*
	 * Initialize timers used by driver
	 */

	/* Heartbeat timer */
	init_timer(&phba->hb_tmofunc);
	phba->hb_tmofunc.function = lpfc_hb_timeout;
	phba->hb_tmofunc.data = (unsigned long)phba;

	psli = &phba->sli;
	/* MBOX heartbeat timer */
	init_timer(&psli->mbox_tmo);
	psli->mbox_tmo.function = lpfc_mbox_timeout;
	psli->mbox_tmo.data = (unsigned long) phba;
	/* FCP polling mode timer */
	init_timer(&phba->fcp_poll_timer);
	phba->fcp_poll_timer.function = lpfc_poll_timeout;
	phba->fcp_poll_timer.data = (unsigned long) phba;
	/* Fabric block timer */
	init_timer(&phba->fabric_block_timer);
	phba->fabric_block_timer.function = lpfc_fabric_block_timeout;
	phba->fabric_block_timer.data = (unsigned long) phba;
	/* EA polling mode timer */
	init_timer(&phba->eratt_poll);
	phba->eratt_poll.function = lpfc_poll_eratt;
	phba->eratt_poll.data = (unsigned long) phba;

	/* Host attention work mask setup */
	phba->work_ha_mask = (HA_ERATT | HA_MBATT | HA_LATT);
	phba->work_ha_mask |= (HA_RXMASK << (LPFC_ELS_RING * 4));

	/* Get all the module params for configuring this host */
	lpfc_get_cfgparam(phba);
	if (phba->pcidev->device == PCI_DEVICE_ID_HORNET) {
		phba->menlo_flag |= HBA_MENLO_SUPPORT;
		/* check for menlo minimum sg count */
		if (phba->cfg_sg_seg_cnt < LPFC_DEFAULT_MENLO_SG_SEG_CNT)
			phba->cfg_sg_seg_cnt = LPFC_DEFAULT_MENLO_SG_SEG_CNT;
	}

	if (!phba->sli.ring)
		phba->sli.ring = (struct lpfc_sli_ring *)
			kzalloc(LPFC_SLI3_MAX_RING *
			sizeof(struct lpfc_sli_ring), GFP_KERNEL);
	if (!phba->sli.ring)
		return -ENOMEM;

	/*
	 * Since lpfc_sg_seg_cnt is module parameter, the sg_dma_buf_size
	 * used to create the sg_dma_buf_pool must be dynamically calculated.
	 */

	/* Initialize the host templates the configured values. */
	lpfc_vport_template.sg_tablesize = phba->cfg_sg_seg_cnt;
	lpfc_template.sg_tablesize = phba->cfg_sg_seg_cnt;

	/* There are going to be 2 reserved BDEs: 1 FCP cmnd + 1 FCP rsp */
	if (phba->cfg_enable_bg) {
		/*
		 * The scsi_buf for a T10-DIF I/O will hold the FCP cmnd,
		 * the FCP rsp, and a BDE for each. Sice we have no control
		 * over how many protection data segments the SCSI Layer
		 * will hand us (ie: there could be one for every block
		 * in the IO), we just allocate enough BDEs to accomidate
		 * our max amount and we need to limit lpfc_sg_seg_cnt to
		 * minimize the risk of running out.
		 */
		phba->cfg_sg_dma_buf_size = sizeof(struct fcp_cmnd) +
			sizeof(struct fcp_rsp) +
			(LPFC_MAX_SG_SEG_CNT * sizeof(struct ulp_bde64));

		if (phba->cfg_sg_seg_cnt > LPFC_MAX_SG_SEG_CNT_DIF)
			phba->cfg_sg_seg_cnt = LPFC_MAX_SG_SEG_CNT_DIF;

		/* Total BDEs in BPL for scsi_sg_list and scsi_sg_prot_list */
		phba->cfg_total_seg_cnt = LPFC_MAX_SG_SEG_CNT;
	} else {
		/*
		 * The scsi_buf for a regular I/O will hold the FCP cmnd,
		 * the FCP rsp, a BDE for each, and a BDE for up to
		 * cfg_sg_seg_cnt data segments.
		 */
		phba->cfg_sg_dma_buf_size = sizeof(struct fcp_cmnd) +
			sizeof(struct fcp_rsp) +
			((phba->cfg_sg_seg_cnt + 2) * sizeof(struct ulp_bde64));

		/* Total BDEs in BPL for scsi_sg_list */
		phba->cfg_total_seg_cnt = phba->cfg_sg_seg_cnt + 2;
	}

	lpfc_printf_log(phba, KERN_INFO, LOG_INIT | LOG_FCP,
			"9088 sg_tablesize:%d dmabuf_size:%d total_bde:%d\n",
			phba->cfg_sg_seg_cnt, phba->cfg_sg_dma_buf_size,
			phba->cfg_total_seg_cnt);

	phba->max_vpi = LPFC_MAX_VPI;
	/* This will be set to correct value after config_port mbox */
	phba->max_vports = 0;

	/*
	 * Initialize the SLI Layer to run with lpfc HBAs.
	 */
	lpfc_sli_setup(phba);
	lpfc_sli_queue_setup(phba);

	/* Allocate device driver memory */
	if (lpfc_mem_alloc(phba, BPL_ALIGN_SZ))
		return -ENOMEM;

	/*
	 * Enable sr-iov virtual functions if supported and configured
	 * through the module parameter.
	 */
	if (phba->cfg_sriov_nr_virtfn > 0) {
		rc = lpfc_sli_probe_sriov_nr_virtfn(phba,
						 phba->cfg_sriov_nr_virtfn);
		if (rc) {
			lpfc_printf_log(phba, KERN_WARNING, LOG_INIT,
					"2808 Requested number of SR-IOV "
					"virtual functions (%d) is not "
					"supported\n",
					phba->cfg_sriov_nr_virtfn);
			phba->cfg_sriov_nr_virtfn = 0;
		}
	}

	return 0;
}