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
struct megasas_irq_context {struct megasas_instance* instance; } ;
struct megasas_instance {int /*<<< orphan*/  hba_lock; int /*<<< orphan*/  fw_reset_no_pci_access; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  DID_OK ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  megasas_deplete_reply_queue (struct megasas_instance*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static irqreturn_t megasas_isr(int irq, void *devp)
{
	struct megasas_irq_context *irq_context = devp;
	struct megasas_instance *instance = irq_context->instance;
	unsigned long flags;
	irqreturn_t	rc;

	if (atomic_read(&instance->fw_reset_no_pci_access))
		return IRQ_HANDLED;

	spin_lock_irqsave(&instance->hba_lock, flags);
	rc =  megasas_deplete_reply_queue(instance, DID_OK);
	spin_unlock_irqrestore(&instance->hba_lock, flags);

	return rc;
}