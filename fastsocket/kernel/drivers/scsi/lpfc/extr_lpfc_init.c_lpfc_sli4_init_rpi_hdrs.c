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
struct lpfc_rpi_hdr {int dummy; } ;
struct TYPE_2__ {scalar_t__ extents_in_use; int /*<<< orphan*/  rpi_hdrs_in_use; int /*<<< orphan*/  lpfc_rpi_hdr_list; } ;
struct lpfc_hba {TYPE_1__ sli4_hba; } ;

/* Variables and functions */
 int EIO ; 
 int ENODEV ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int LOG_MBOX ; 
 int LOG_SLI ; 
 int /*<<< orphan*/  lpfc_printf_log (struct lpfc_hba*,int /*<<< orphan*/ ,int,char*) ; 
 struct lpfc_rpi_hdr* lpfc_sli4_create_rpi_hdr (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_sli4_remove_rpis (struct lpfc_hba*) ; 

int
lpfc_sli4_init_rpi_hdrs(struct lpfc_hba *phba)
{
	int rc = 0;
	struct lpfc_rpi_hdr *rpi_hdr;

	INIT_LIST_HEAD(&phba->sli4_hba.lpfc_rpi_hdr_list);
	if (!phba->sli4_hba.rpi_hdrs_in_use)
		return rc;
	if (phba->sli4_hba.extents_in_use)
		return -EIO;

	rpi_hdr = lpfc_sli4_create_rpi_hdr(phba);
	if (!rpi_hdr) {
		lpfc_printf_log(phba, KERN_ERR, LOG_MBOX | LOG_SLI,
				"0391 Error during rpi post operation\n");
		lpfc_sli4_remove_rpis(phba);
		rc = -ENODEV;
	}

	return rc;
}