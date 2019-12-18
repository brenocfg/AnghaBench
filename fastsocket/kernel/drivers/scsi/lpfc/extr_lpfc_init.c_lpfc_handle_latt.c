#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct lpfc_vport {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  link_event; } ;
struct lpfc_sli {int /*<<< orphan*/  sli_flag; TYPE_2__* ring; TYPE_1__ slistat; } ;
struct lpfc_hba {int /*<<< orphan*/  link_state; int /*<<< orphan*/  hbalock; int /*<<< orphan*/  HAregaddr; int /*<<< orphan*/  HCregaddr; int /*<<< orphan*/  mbox_mem_pool; struct lpfc_sli sli; struct lpfc_vport* pport; } ;
struct lpfc_dmabuf {int /*<<< orphan*/  phys; int /*<<< orphan*/  virt; } ;
struct TYPE_9__ {struct lpfc_vport* vport; int /*<<< orphan*/  mbox_cmpl; } ;
struct TYPE_8__ {int /*<<< orphan*/  flag; } ;
typedef  TYPE_3__ LPFC_MBOXQ_t ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  volatile HA_LATT ; 
 int /*<<< orphan*/  volatile HC_LAINT_ENA ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  LOG_MBOX ; 
 size_t LPFC_ELS_RING ; 
 int /*<<< orphan*/  LPFC_HBA_ERROR ; 
 int /*<<< orphan*/  LPFC_PROCESS_LA ; 
 int /*<<< orphan*/  LPFC_STOP_IOCB_EVENT ; 
 int MBX_NOT_FINISHED ; 
 int /*<<< orphan*/  MBX_NOWAIT ; 
 int /*<<< orphan*/  kfree (struct lpfc_dmabuf*) ; 
 struct lpfc_dmabuf* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_els_flush_all_cmd (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_linkdown (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_mbuf_alloc (struct lpfc_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lpfc_mbuf_free (struct lpfc_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_mbx_cmpl_read_topology ; 
 int /*<<< orphan*/  lpfc_printf_log (struct lpfc_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  lpfc_read_topology (struct lpfc_hba*,TYPE_3__*,struct lpfc_dmabuf*) ; 
 int lpfc_sli_issue_mbox (struct lpfc_hba*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ mempool_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mempool_free (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/  volatile,int /*<<< orphan*/ ) ; 

void
lpfc_handle_latt(struct lpfc_hba *phba)
{
	struct lpfc_vport *vport = phba->pport;
	struct lpfc_sli   *psli = &phba->sli;
	LPFC_MBOXQ_t *pmb;
	volatile uint32_t control;
	struct lpfc_dmabuf *mp;
	int rc = 0;

	pmb = (LPFC_MBOXQ_t *)mempool_alloc(phba->mbox_mem_pool, GFP_KERNEL);
	if (!pmb) {
		rc = 1;
		goto lpfc_handle_latt_err_exit;
	}

	mp = kmalloc(sizeof(struct lpfc_dmabuf), GFP_KERNEL);
	if (!mp) {
		rc = 2;
		goto lpfc_handle_latt_free_pmb;
	}

	mp->virt = lpfc_mbuf_alloc(phba, 0, &mp->phys);
	if (!mp->virt) {
		rc = 3;
		goto lpfc_handle_latt_free_mp;
	}

	/* Cleanup any outstanding ELS commands */
	lpfc_els_flush_all_cmd(phba);

	psli->slistat.link_event++;
	lpfc_read_topology(phba, pmb, mp);
	pmb->mbox_cmpl = lpfc_mbx_cmpl_read_topology;
	pmb->vport = vport;
	/* Block ELS IOCBs until we have processed this mbox command */
	phba->sli.ring[LPFC_ELS_RING].flag |= LPFC_STOP_IOCB_EVENT;
	rc = lpfc_sli_issue_mbox (phba, pmb, MBX_NOWAIT);
	if (rc == MBX_NOT_FINISHED) {
		rc = 4;
		goto lpfc_handle_latt_free_mbuf;
	}

	/* Clear Link Attention in HA REG */
	spin_lock_irq(&phba->hbalock);
	writel(HA_LATT, phba->HAregaddr);
	readl(phba->HAregaddr); /* flush */
	spin_unlock_irq(&phba->hbalock);

	return;

lpfc_handle_latt_free_mbuf:
	phba->sli.ring[LPFC_ELS_RING].flag &= ~LPFC_STOP_IOCB_EVENT;
	lpfc_mbuf_free(phba, mp->virt, mp->phys);
lpfc_handle_latt_free_mp:
	kfree(mp);
lpfc_handle_latt_free_pmb:
	mempool_free(pmb, phba->mbox_mem_pool);
lpfc_handle_latt_err_exit:
	/* Enable Link attention interrupts */
	spin_lock_irq(&phba->hbalock);
	psli->sli_flag |= LPFC_PROCESS_LA;
	control = readl(phba->HCregaddr);
	control |= HC_LAINT_ENA;
	writel(control, phba->HCregaddr);
	readl(phba->HCregaddr); /* flush */

	/* Clear Link Attention in HA REG */
	writel(HA_LATT, phba->HAregaddr);
	readl(phba->HAregaddr); /* flush */
	spin_unlock_irq(&phba->hbalock);
	lpfc_linkdown(phba);
	phba->link_state = LPFC_HBA_ERROR;

	lpfc_printf_log(phba, KERN_ERR, LOG_MBOX,
		     "0300 LATT: Cannot issue READ_LA: Data:%d\n", rc);

	return;
}