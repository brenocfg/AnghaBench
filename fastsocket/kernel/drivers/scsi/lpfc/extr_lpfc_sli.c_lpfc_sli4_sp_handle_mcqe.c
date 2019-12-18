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
struct lpfc_mcqe {int dummy; } ;
struct lpfc_hba {int dummy; } ;
struct lpfc_cqe {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bf_get (int /*<<< orphan*/ ,struct lpfc_mcqe*) ; 
 int lpfc_sli4_sp_handle_async_event (struct lpfc_hba*,struct lpfc_mcqe*) ; 
 int lpfc_sli4_sp_handle_mbox_event (struct lpfc_hba*,struct lpfc_mcqe*) ; 
 int /*<<< orphan*/  lpfc_sli_pcimem_bcopy (struct lpfc_cqe*,struct lpfc_mcqe*,int) ; 
 int /*<<< orphan*/  lpfc_trailer_async ; 

__attribute__((used)) static bool
lpfc_sli4_sp_handle_mcqe(struct lpfc_hba *phba, struct lpfc_cqe *cqe)
{
	struct lpfc_mcqe mcqe;
	bool workposted;

	/* Copy the mailbox MCQE and convert endian order as needed */
	lpfc_sli_pcimem_bcopy(cqe, &mcqe, sizeof(struct lpfc_mcqe));

	/* Invoke the proper event handling routine */
	if (!bf_get(lpfc_trailer_async, &mcqe))
		workposted = lpfc_sli4_sp_handle_mbox_event(phba, &mcqe);
	else
		workposted = lpfc_sli4_sp_handle_async_event(phba, &mcqe);
	return workposted;
}