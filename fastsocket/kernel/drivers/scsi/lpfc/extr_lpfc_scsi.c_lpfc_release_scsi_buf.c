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
struct lpfc_scsi_buf {int dummy; } ;
struct lpfc_hba {int /*<<< orphan*/  (* lpfc_release_scsi_buf ) (struct lpfc_hba*,struct lpfc_scsi_buf*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct lpfc_hba*,struct lpfc_scsi_buf*) ; 

__attribute__((used)) static void
lpfc_release_scsi_buf(struct lpfc_hba *phba, struct lpfc_scsi_buf *psb)
{

	phba->lpfc_release_scsi_buf(phba, psb);
}