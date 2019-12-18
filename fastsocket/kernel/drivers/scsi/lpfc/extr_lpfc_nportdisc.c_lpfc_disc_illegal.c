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
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct lpfc_vport {struct lpfc_hba* phba; } ;
struct lpfc_nodelist {scalar_t__ nlp_state; int /*<<< orphan*/  nlp_flag; int /*<<< orphan*/  nlp_rpi; int /*<<< orphan*/  nlp_DID; } ;
struct lpfc_hba {TYPE_1__* pport; } ;
struct TYPE_7__ {int /*<<< orphan*/ * varWords; } ;
struct TYPE_9__ {TYPE_2__ un; int /*<<< orphan*/  mbxStatus; } ;
struct TYPE_8__ {TYPE_4__ mb; } ;
struct TYPE_10__ {TYPE_3__ u; } ;
struct TYPE_6__ {int load_flag; } ;
typedef  TYPE_4__ MAILBOX_t ;
typedef  TYPE_5__ LPFC_MBOXQ_t ;

/* Variables and functions */
 int FC_UNLOADING ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  LOG_DISCOVERY ; 
 scalar_t__ NLP_EVT_CMPL_REG_LOGIN ; 
 int /*<<< orphan*/  lpfc_printf_vlog (struct lpfc_vport*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_release_rpi (struct lpfc_hba*,struct lpfc_vport*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint32_t
lpfc_disc_illegal(struct lpfc_vport *vport, struct lpfc_nodelist *ndlp,
		  void *arg, uint32_t evt)
{
	struct lpfc_hba *phba;
	LPFC_MBOXQ_t *pmb = (LPFC_MBOXQ_t *) arg;
	MAILBOX_t *mb;
	uint16_t rpi;

	phba = vport->phba;
	/* Release the RPI if reglogin completing */
	if (!(phba->pport->load_flag & FC_UNLOADING) &&
		(evt == NLP_EVT_CMPL_REG_LOGIN) &&
		(!pmb->u.mb.mbxStatus)) {
		mb = &pmb->u.mb;
		rpi = pmb->u.mb.un.varWords[0];
		lpfc_release_rpi(phba, vport, rpi);
	}
	lpfc_printf_vlog(vport, KERN_ERR, LOG_DISCOVERY,
			 "0271 Illegal State Transition: node x%x "
			 "event x%x, state x%x Data: x%x x%x\n",
			 ndlp->nlp_DID, evt, ndlp->nlp_state, ndlp->nlp_rpi,
			 ndlp->nlp_flag);
	return ndlp->nlp_state;
}