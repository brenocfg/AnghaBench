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
struct megasas_instance {int /*<<< orphan*/  work_init; int /*<<< orphan*/  fw_outstanding; scalar_t__ issuepend_done; int /*<<< orphan*/  adprecovery; TYPE_1__* instancet; int /*<<< orphan*/ * consumer; TYPE_2__* pdev; } ;
struct TYPE_4__ {scalar_t__ device; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* disable_intr ) (struct megasas_instance*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  MEGASAS_ADPRESET_INPROG_SIGN ; 
 int /*<<< orphan*/  MEGASAS_ADPRESET_SM_INFAULT ; 
 scalar_t__ PCI_DEVICE_ID_DELL_PERC5 ; 
 scalar_t__ PCI_DEVICE_ID_LSI_SAS1064R ; 
 scalar_t__ PCI_DEVICE_ID_LSI_VERDE_ZCR ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  megasas_internal_reset_defer_cmds (struct megasas_instance*) ; 
 int /*<<< orphan*/  process_fw_state_change_wq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct megasas_instance*) ; 

void megasas_do_ocr(struct megasas_instance *instance)
{
	if ((instance->pdev->device == PCI_DEVICE_ID_LSI_SAS1064R) ||
	(instance->pdev->device == PCI_DEVICE_ID_DELL_PERC5) ||
	(instance->pdev->device == PCI_DEVICE_ID_LSI_VERDE_ZCR)) {
		*instance->consumer     = MEGASAS_ADPRESET_INPROG_SIGN;
	}
	instance->instancet->disable_intr(instance);
	instance->adprecovery   = MEGASAS_ADPRESET_SM_INFAULT;
	instance->issuepend_done = 0;

	atomic_set(&instance->fw_outstanding, 0);
	megasas_internal_reset_defer_cmds(instance);
	process_fw_state_change_wq(&instance->work_init);
}