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
struct hwi_wrb_context {int /*<<< orphan*/  pwrb_handle_basestd; int /*<<< orphan*/  pwrb_handle_base; } ;
struct hwi_controller {struct hwi_wrb_context* wrb_context; } ;
struct TYPE_2__ {unsigned int cxns_per_ctrl; } ;
struct beiscsi_hba {TYPE_1__ params; struct hwi_controller* phwi_ctrlr; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void free_wrb_handles(struct beiscsi_hba *phba)
{
	unsigned int index;
	struct hwi_controller *phwi_ctrlr;
	struct hwi_wrb_context *pwrb_context;

	phwi_ctrlr = phba->phwi_ctrlr;
	for (index = 0; index < phba->params.cxns_per_ctrl; index++) {
		pwrb_context = &phwi_ctrlr->wrb_context[index];
		kfree(pwrb_context->pwrb_handle_base);
		kfree(pwrb_context->pwrb_handle_basestd);
	}
}