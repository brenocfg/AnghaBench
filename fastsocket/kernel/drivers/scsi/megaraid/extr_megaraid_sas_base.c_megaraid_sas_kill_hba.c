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
struct megasas_instance {TYPE_1__* reg_set; TYPE_2__* pdev; } ;
struct TYPE_4__ {scalar_t__ device; } ;
struct TYPE_3__ {int /*<<< orphan*/  inbound_doorbell; int /*<<< orphan*/  doorbell; } ;

/* Variables and functions */
 int /*<<< orphan*/  MFI_STOP_ADP ; 
 scalar_t__ PCI_DEVICE_ID_LSI_FURY ; 
 scalar_t__ PCI_DEVICE_ID_LSI_FUSION ; 
 scalar_t__ PCI_DEVICE_ID_LSI_INVADER ; 
 scalar_t__ PCI_DEVICE_ID_LSI_SAS0071SKINNY ; 
 scalar_t__ PCI_DEVICE_ID_LSI_SAS0073SKINNY ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void megaraid_sas_kill_hba(struct megasas_instance *instance)
{
	if ((instance->pdev->device == PCI_DEVICE_ID_LSI_SAS0073SKINNY) ||
	    (instance->pdev->device == PCI_DEVICE_ID_LSI_SAS0071SKINNY) ||
	    (instance->pdev->device == PCI_DEVICE_ID_LSI_FUSION) ||
	    (instance->pdev->device == PCI_DEVICE_ID_LSI_INVADER) ||
	    (instance->pdev->device == PCI_DEVICE_ID_LSI_FURY)) {
		writel(MFI_STOP_ADP, &instance->reg_set->doorbell);
	} else {
		writel(MFI_STOP_ADP, &instance->reg_set->inbound_doorbell);
	}
}