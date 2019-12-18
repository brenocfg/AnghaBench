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
struct isac {struct fritz_adapter* priv; } ;
struct fritz_adapter {int /*<<< orphan*/  hw_lock; scalar_t__ io; } ;

/* Variables and functions */
 scalar_t__ AVM_DATA ; 
 int /*<<< orphan*/  AVM_IDX_ISAC_FIFO ; 
 scalar_t__ AVM_INDEX ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  outsb (scalar_t__,unsigned char*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void fcpci_write_isac_fifo(struct isac *isac, unsigned char * data, 
				  int size)
{
	struct fritz_adapter *adapter = isac->priv;
	unsigned long flags;

	spin_lock_irqsave(&adapter->hw_lock, flags);
	outb(AVM_IDX_ISAC_FIFO, adapter->io + AVM_INDEX);
	outsb(adapter->io + AVM_DATA, data, size);
 	spin_unlock_irqrestore(&adapter->hw_lock, flags);
}