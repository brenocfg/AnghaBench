#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct lpfc_vport {struct lpfc_hba* phba; } ;
struct lpfc_nodelist {int /*<<< orphan*/  nlp_state; int /*<<< orphan*/  nlp_sid; } ;
struct lpfc_iocbq {int dummy; } ;
struct TYPE_2__ {size_t fcp_ring; int /*<<< orphan*/ * ring; } ;
struct lpfc_hba {TYPE_1__ sli; } ;

/* Variables and functions */
 int /*<<< orphan*/  ELS_CMD_PRLO ; 
 int /*<<< orphan*/  LPFC_CTX_TGT ; 
 int /*<<< orphan*/  lpfc_rcv_logo (struct lpfc_vport*,struct lpfc_nodelist*,struct lpfc_iocbq*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_sli_abort_iocb (struct lpfc_vport*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint32_t
lpfc_rcv_prlo_mapped_node(struct lpfc_vport *vport, struct lpfc_nodelist *ndlp,
			  void *arg, uint32_t evt)
{
	struct lpfc_hba  *phba = vport->phba;
	struct lpfc_iocbq *cmdiocb = (struct lpfc_iocbq *) arg;

	/* flush the target */
	lpfc_sli_abort_iocb(vport, &phba->sli.ring[phba->sli.fcp_ring],
			    ndlp->nlp_sid, 0, LPFC_CTX_TGT);

	/* Treat like rcv logo */
	lpfc_rcv_logo(vport, ndlp, cmdiocb, ELS_CMD_PRLO);
	return ndlp->nlp_state;
}