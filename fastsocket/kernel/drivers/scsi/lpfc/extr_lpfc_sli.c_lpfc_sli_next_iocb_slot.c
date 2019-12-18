#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_3__ {scalar_t__ numCiocb; scalar_t__ next_cmdidx; scalar_t__ cmdidx; scalar_t__ local_getidx; } ;
struct TYPE_4__ {TYPE_1__ sli3; } ;
struct lpfc_sli_ring {size_t ringno; TYPE_2__ sli; } ;
struct lpfc_pgp {int /*<<< orphan*/  cmdGetInx; } ;
struct lpfc_hba {int /*<<< orphan*/  work_hs; int /*<<< orphan*/  work_ha; int /*<<< orphan*/  link_state; struct lpfc_pgp* port_gp; } ;
typedef  int /*<<< orphan*/  IOCB_t ;

/* Variables and functions */
 int /*<<< orphan*/  HA_ERATT ; 
 int /*<<< orphan*/  HS_FFER3 ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  LOG_SLI ; 
 int /*<<< orphan*/  LPFC_HBA_ERROR ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * lpfc_cmd_iocb (struct lpfc_hba*,struct lpfc_sli_ring*) ; 
 int /*<<< orphan*/  lpfc_printf_log (struct lpfc_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,size_t,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  lpfc_worker_wake_up (struct lpfc_hba*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static IOCB_t *
lpfc_sli_next_iocb_slot (struct lpfc_hba *phba, struct lpfc_sli_ring *pring)
{
	struct lpfc_pgp *pgp = &phba->port_gp[pring->ringno];
	uint32_t  max_cmd_idx = pring->sli.sli3.numCiocb;
	if ((pring->sli.sli3.next_cmdidx == pring->sli.sli3.cmdidx) &&
	   (++pring->sli.sli3.next_cmdidx >= max_cmd_idx))
		pring->sli.sli3.next_cmdidx = 0;

	if (unlikely(pring->sli.sli3.local_getidx ==
		pring->sli.sli3.next_cmdidx)) {

		pring->sli.sli3.local_getidx = le32_to_cpu(pgp->cmdGetInx);

		if (unlikely(pring->sli.sli3.local_getidx >= max_cmd_idx)) {
			lpfc_printf_log(phba, KERN_ERR, LOG_SLI,
					"0315 Ring %d issue: portCmdGet %d "
					"is bigger than cmd ring %d\n",
					pring->ringno,
					pring->sli.sli3.local_getidx,
					max_cmd_idx);

			phba->link_state = LPFC_HBA_ERROR;
			/*
			 * All error attention handlers are posted to
			 * worker thread
			 */
			phba->work_ha |= HA_ERATT;
			phba->work_hs = HS_FFER3;

			lpfc_worker_wake_up(phba);

			return NULL;
		}

		if (pring->sli.sli3.local_getidx == pring->sli.sli3.next_cmdidx)
			return NULL;
	}

	return lpfc_cmd_iocb(phba, pring);
}