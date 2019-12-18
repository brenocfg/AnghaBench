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
typedef  size_t uint16_t ;
struct wrb_handle {int /*<<< orphan*/  wrb_index; int /*<<< orphan*/  nxt_wrb_index; } ;
struct hwi_wrb_context {int wrb_handles_available; size_t alloc_index; struct wrb_handle** pwrb_handle_base; } ;
struct hwi_controller {struct hwi_wrb_context* wrb_context; } ;
struct TYPE_2__ {int wrbs_per_cxn; } ;
struct beiscsi_hba {TYPE_1__ params; struct hwi_controller* phwi_ctrlr; } ;

/* Variables and functions */
 size_t BE_GET_CRI_FROM_CID (unsigned int) ; 

struct wrb_handle *alloc_wrb_handle(struct beiscsi_hba *phba, unsigned int cid)
{
	struct hwi_wrb_context *pwrb_context;
	struct hwi_controller *phwi_ctrlr;
	struct wrb_handle *pwrb_handle, *pwrb_handle_tmp;
	uint16_t cri_index = BE_GET_CRI_FROM_CID(cid);

	phwi_ctrlr = phba->phwi_ctrlr;
	pwrb_context = &phwi_ctrlr->wrb_context[cri_index];
	if (pwrb_context->wrb_handles_available >= 2) {
		pwrb_handle = pwrb_context->pwrb_handle_base[
					    pwrb_context->alloc_index];
		pwrb_context->wrb_handles_available--;
		if (pwrb_context->alloc_index ==
						(phba->params.wrbs_per_cxn - 1))
			pwrb_context->alloc_index = 0;
		else
			pwrb_context->alloc_index++;
		pwrb_handle_tmp = pwrb_context->pwrb_handle_base[
						pwrb_context->alloc_index];
		pwrb_handle->nxt_wrb_index = pwrb_handle_tmp->wrb_index;
	} else
		pwrb_handle = NULL;
	return pwrb_handle;
}