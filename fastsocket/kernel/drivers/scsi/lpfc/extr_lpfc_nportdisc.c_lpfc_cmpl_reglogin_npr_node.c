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
typedef  int /*<<< orphan*/  uint32_t ;
struct lpfc_vport {TYPE_3__* phba; } ;
struct lpfc_nodelist {int nlp_flag; int /*<<< orphan*/  nlp_state; int /*<<< orphan*/  nlp_rpi; } ;
struct TYPE_6__ {int /*<<< orphan*/ * varWords; } ;
struct TYPE_9__ {TYPE_1__ un; int /*<<< orphan*/  mbxStatus; } ;
struct TYPE_7__ {TYPE_4__ mb; } ;
struct TYPE_10__ {TYPE_2__ u; } ;
struct TYPE_8__ {scalar_t__ sli_rev; } ;
typedef  TYPE_4__ MAILBOX_t ;
typedef  TYPE_5__ LPFC_MBOXQ_t ;

/* Variables and functions */
 scalar_t__ LPFC_SLI_REV4 ; 
 int NLP_NODEV_REMOVE ; 
 int NLP_RPI_REGISTERED ; 
 int /*<<< orphan*/  NLP_STE_FREED_NODE ; 
 int /*<<< orphan*/  lpfc_drop_node (struct lpfc_vport*,struct lpfc_nodelist*) ; 

__attribute__((used)) static uint32_t
lpfc_cmpl_reglogin_npr_node(struct lpfc_vport *vport,
			    struct lpfc_nodelist *ndlp,
			    void *arg, uint32_t evt)
{
	LPFC_MBOXQ_t *pmb = (LPFC_MBOXQ_t *) arg;
	MAILBOX_t    *mb = &pmb->u.mb;

	if (!mb->mbxStatus) {
		/* SLI4 ports have preallocated logical rpis. */
		if (vport->phba->sli_rev < LPFC_SLI_REV4)
			ndlp->nlp_rpi = mb->un.varWords[0];
		ndlp->nlp_flag |= NLP_RPI_REGISTERED;
	} else {
		if (ndlp->nlp_flag & NLP_NODEV_REMOVE) {
			lpfc_drop_node(vport, ndlp);
			return NLP_STE_FREED_NODE;
		}
	}
	return ndlp->nlp_state;
}