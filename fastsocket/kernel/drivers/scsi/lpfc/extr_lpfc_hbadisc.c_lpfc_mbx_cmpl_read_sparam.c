#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct serv_parm {int dummy; } ;
struct lpfc_vport {scalar_t__ port_type; int /*<<< orphan*/  fc_portname; int /*<<< orphan*/  fc_nodename; int /*<<< orphan*/  fc_sparam; int /*<<< orphan*/  port_state; } ;
struct lpfc_hba {int /*<<< orphan*/  mbox_mem_pool; int /*<<< orphan*/  wwpn; int /*<<< orphan*/  wwnn; } ;
struct lpfc_dmabuf {int /*<<< orphan*/  phys; scalar_t__ virt; } ;
struct TYPE_7__ {scalar_t__ mbxStatus; } ;
struct TYPE_6__ {TYPE_2__ mb; } ;
struct TYPE_8__ {int /*<<< orphan*/ * context1; struct lpfc_vport* vport; TYPE_1__ u; } ;
typedef  TYPE_2__ MAILBOX_t ;
typedef  TYPE_3__ LPFC_MBOXQ_t ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  LOG_MBOX ; 
 scalar_t__ LPFC_PHYSICAL_PORT ; 
 int /*<<< orphan*/  kfree (struct lpfc_dmabuf*) ; 
 int /*<<< orphan*/  lpfc_issue_clear_la (struct lpfc_hba*,struct lpfc_vport*) ; 
 int /*<<< orphan*/  lpfc_linkdown (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_mbuf_free (struct lpfc_hba*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_printf_vlog (struct lpfc_vport*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_update_vport_wwn (struct lpfc_vport*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mempool_free (TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
lpfc_mbx_cmpl_read_sparam(struct lpfc_hba *phba, LPFC_MBOXQ_t *pmb)
{
	MAILBOX_t *mb = &pmb->u.mb;
	struct lpfc_dmabuf *mp = (struct lpfc_dmabuf *) pmb->context1;
	struct lpfc_vport  *vport = pmb->vport;


	/* Check for error */
	if (mb->mbxStatus) {
		/* READ_SPARAM mbox error <mbxStatus> state <hba_state> */
		lpfc_printf_vlog(vport, KERN_ERR, LOG_MBOX,
				 "0319 READ_SPARAM mbxStatus error x%x "
				 "hba state x%x>\n",
				 mb->mbxStatus, vport->port_state);
		lpfc_linkdown(phba);
		goto out;
	}

	memcpy((uint8_t *) &vport->fc_sparam, (uint8_t *) mp->virt,
	       sizeof (struct serv_parm));
	lpfc_update_vport_wwn(vport);
	if (vport->port_type == LPFC_PHYSICAL_PORT) {
		memcpy(&phba->wwnn, &vport->fc_nodename, sizeof(phba->wwnn));
		memcpy(&phba->wwpn, &vport->fc_portname, sizeof(phba->wwnn));
	}

	lpfc_mbuf_free(phba, mp->virt, mp->phys);
	kfree(mp);
	mempool_free(pmb, phba->mbox_mem_pool);
	return;

out:
	pmb->context1 = NULL;
	lpfc_mbuf_free(phba, mp->virt, mp->phys);
	kfree(mp);
	lpfc_issue_clear_la(phba, vport);
	mempool_free(pmb, phba->mbox_mem_pool);
	return;
}