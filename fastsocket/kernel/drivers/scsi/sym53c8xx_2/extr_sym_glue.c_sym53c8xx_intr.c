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
struct sym_data {int /*<<< orphan*/  pdev; } ;
struct Scsi_Host {int /*<<< orphan*/  host_lock; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int DEBUG_FLAGS ; 
 int DEBUG_TINY ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 scalar_t__ pci_channel_offline (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf_debug (char*) ; 
 struct sym_data* shost_priv (struct Scsi_Host*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sym_interrupt (struct Scsi_Host*) ; 

__attribute__((used)) static irqreturn_t sym53c8xx_intr(int irq, void *dev_id)
{
	struct Scsi_Host *shost = dev_id;
	struct sym_data *sym_data = shost_priv(shost);
	irqreturn_t result;

	/* Avoid spinloop trying to handle interrupts on frozen device */
	if (pci_channel_offline(sym_data->pdev))
		return IRQ_NONE;

	if (DEBUG_FLAGS & DEBUG_TINY) printf_debug ("[");

	spin_lock(shost->host_lock);
	result = sym_interrupt(shost);
	spin_unlock(shost->host_lock);

	if (DEBUG_FLAGS & DEBUG_TINY) printf_debug ("]\n");

	return result;
}