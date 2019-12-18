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
typedef  int u32 ;
struct megasas_instance {scalar_t__ msix_vectors; scalar_t__ adprecovery; int /*<<< orphan*/  hba_lock; } ;

/* Variables and functions */
 scalar_t__ MEGASAS_HW_CRITICAL_ERROR ; 
 int /*<<< orphan*/  complete_cmd_fusion (struct megasas_instance*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void
megasas_complete_cmd_dpc_fusion(unsigned long instance_addr)
{
	struct megasas_instance *instance =
		(struct megasas_instance *)instance_addr;
	unsigned long flags;
	u32 count, MSIxIndex;

	count = instance->msix_vectors > 0 ? instance->msix_vectors : 1;

	/* If we have already declared adapter dead, donot complete cmds */
	spin_lock_irqsave(&instance->hba_lock, flags);
	if (instance->adprecovery == MEGASAS_HW_CRITICAL_ERROR) {
		spin_unlock_irqrestore(&instance->hba_lock, flags);
		return;
	}
	spin_unlock_irqrestore(&instance->hba_lock, flags);

	for (MSIxIndex = 0 ; MSIxIndex < count; MSIxIndex++)
		complete_cmd_fusion(instance, MSIxIndex);
}