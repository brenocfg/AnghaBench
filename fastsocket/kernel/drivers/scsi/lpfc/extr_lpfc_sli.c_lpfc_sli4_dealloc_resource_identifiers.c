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
struct TYPE_3__ {scalar_t__ vpi_used; } ;
struct TYPE_4__ {int /*<<< orphan*/  sli4_flags; int /*<<< orphan*/  vfi_ids; int /*<<< orphan*/  vfi_bmask; int /*<<< orphan*/  xri_ids; int /*<<< orphan*/  xri_bmask; TYPE_1__ max_cfg_param; scalar_t__ extents_in_use; } ;
struct lpfc_hba {TYPE_2__ sli4_hba; int /*<<< orphan*/  vpi_ids; int /*<<< orphan*/  vpi_bmask; } ;

/* Variables and functions */
 int /*<<< orphan*/  LPFC_RSC_TYPE_FCOE_RPI ; 
 int /*<<< orphan*/  LPFC_RSC_TYPE_FCOE_VFI ; 
 int /*<<< orphan*/  LPFC_RSC_TYPE_FCOE_VPI ; 
 int /*<<< orphan*/  LPFC_RSC_TYPE_FCOE_XRI ; 
 int /*<<< orphan*/  bf_set (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_idx_rsrc_rdy ; 
 int /*<<< orphan*/  lpfc_sli4_dealloc_extent (struct lpfc_hba*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_vfi_rsrc_rdy ; 
 int /*<<< orphan*/  lpfc_vpi_rsrc_rdy ; 

int
lpfc_sli4_dealloc_resource_identifiers(struct lpfc_hba *phba)
{
	if (phba->sli4_hba.extents_in_use) {
		lpfc_sli4_dealloc_extent(phba, LPFC_RSC_TYPE_FCOE_VPI);
		lpfc_sli4_dealloc_extent(phba, LPFC_RSC_TYPE_FCOE_RPI);
		lpfc_sli4_dealloc_extent(phba, LPFC_RSC_TYPE_FCOE_XRI);
		lpfc_sli4_dealloc_extent(phba, LPFC_RSC_TYPE_FCOE_VFI);
	} else {
		kfree(phba->vpi_bmask);
		phba->sli4_hba.max_cfg_param.vpi_used = 0;
		kfree(phba->vpi_ids);
		bf_set(lpfc_vpi_rsrc_rdy, &phba->sli4_hba.sli4_flags, 0);
		kfree(phba->sli4_hba.xri_bmask);
		kfree(phba->sli4_hba.xri_ids);
		kfree(phba->sli4_hba.vfi_bmask);
		kfree(phba->sli4_hba.vfi_ids);
		bf_set(lpfc_vfi_rsrc_rdy, &phba->sli4_hba.sli4_flags, 0);
		bf_set(lpfc_idx_rsrc_rdy, &phba->sli4_hba.sli4_flags, 0);
	}

	return 0;
}