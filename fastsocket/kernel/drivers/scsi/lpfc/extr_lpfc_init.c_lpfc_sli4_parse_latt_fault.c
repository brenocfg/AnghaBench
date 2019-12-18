#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct lpfc_hba {int dummy; } ;
struct lpfc_acqe_link {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  LOG_INIT ; 
#define  LPFC_ASYNC_LINK_FAULT_LOCAL 130 
#define  LPFC_ASYNC_LINK_FAULT_NONE 129 
#define  LPFC_ASYNC_LINK_FAULT_REMOTE 128 
 int /*<<< orphan*/  MBXERR_ERROR ; 
 int bf_get (int /*<<< orphan*/ ,struct lpfc_acqe_link*) ; 
 int /*<<< orphan*/  lpfc_acqe_link_fault ; 
 int /*<<< orphan*/  lpfc_printf_log (struct lpfc_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static uint16_t
lpfc_sli4_parse_latt_fault(struct lpfc_hba *phba,
			   struct lpfc_acqe_link *acqe_link)
{
	uint16_t latt_fault;

	switch (bf_get(lpfc_acqe_link_fault, acqe_link)) {
	case LPFC_ASYNC_LINK_FAULT_NONE:
	case LPFC_ASYNC_LINK_FAULT_LOCAL:
	case LPFC_ASYNC_LINK_FAULT_REMOTE:
		latt_fault = 0;
		break;
	default:
		lpfc_printf_log(phba, KERN_ERR, LOG_INIT,
				"0398 Invalid link fault code: x%x\n",
				bf_get(lpfc_acqe_link_fault, acqe_link));
		latt_fault = MBXERR_ERROR;
		break;
	}
	return latt_fault;
}