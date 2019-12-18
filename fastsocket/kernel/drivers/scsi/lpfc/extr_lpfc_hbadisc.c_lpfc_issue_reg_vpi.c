#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct lpfc_vport {int dummy; } ;
struct lpfc_hba {int /*<<< orphan*/  mbox_mem_pool; } ;
struct TYPE_6__ {struct lpfc_vport* vport; int /*<<< orphan*/  mbox_cmpl; } ;
typedef  TYPE_1__ LPFC_MBOXQ_t ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ MBX_NOT_FINISHED ; 
 int /*<<< orphan*/  MBX_NOWAIT ; 
 int /*<<< orphan*/  lpfc_mbx_cmpl_reg_vpi ; 
 int /*<<< orphan*/  lpfc_reg_vpi (struct lpfc_vport*,TYPE_1__*) ; 
 scalar_t__ lpfc_sli_issue_mbox (struct lpfc_hba*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* mempool_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mempool_free (TYPE_1__*,int /*<<< orphan*/ ) ; 

void
lpfc_issue_reg_vpi(struct lpfc_hba *phba, struct lpfc_vport *vport)
{
	LPFC_MBOXQ_t *regvpimbox;

	regvpimbox = mempool_alloc(phba->mbox_mem_pool, GFP_KERNEL);
	if (regvpimbox) {
		lpfc_reg_vpi(vport, regvpimbox);
		regvpimbox->mbox_cmpl = lpfc_mbx_cmpl_reg_vpi;
		regvpimbox->vport = vport;
		if (lpfc_sli_issue_mbox(phba, regvpimbox, MBX_NOWAIT)
					== MBX_NOT_FINISHED) {
			mempool_free(regvpimbox, phba->mbox_mem_pool);
		}
	}
}