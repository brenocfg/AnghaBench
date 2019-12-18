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
struct lpfc_vport {TYPE_1__* phba; } ;
struct lpfc_nodelist {int dummy; } ;
struct lpfc_iocbq {int dummy; } ;
struct TYPE_2__ {scalar_t__ sli_rev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ELS_CMD_ACC ; 
 scalar_t__ LPFC_SLI_REV4 ; 
 int /*<<< orphan*/  lpfc_els_clear_rrq (struct lpfc_vport*,struct lpfc_iocbq*,struct lpfc_nodelist*) ; 
 int /*<<< orphan*/  lpfc_els_rsp_acc (struct lpfc_vport*,int /*<<< orphan*/ ,struct lpfc_iocbq*,struct lpfc_nodelist*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
lpfc_els_rcv_rrq(struct lpfc_vport *vport, struct lpfc_iocbq *cmdiocb,
		 struct lpfc_nodelist *ndlp)
{
	lpfc_els_rsp_acc(vport, ELS_CMD_ACC, cmdiocb, ndlp, NULL);
	if (vport->phba->sli_rev == LPFC_SLI_REV4)
		lpfc_els_clear_rrq(vport, cmdiocb, ndlp);
}