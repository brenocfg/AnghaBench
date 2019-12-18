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
 unsigned char AVM_IDX_ISAC_REG_HIGH ; 
 unsigned char AVM_IDX_ISAC_REG_LOW ; 
 scalar_t__ AVM_INDEX ; 
 int /*<<< orphan*/  DBG (int,char*,unsigned char,unsigned char) ; 
 int /*<<< orphan*/  outb (unsigned char,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void fcpci_write_isac(struct isac *isac, unsigned char offset,
			     unsigned char value)
{
	struct fritz_adapter *adapter = isac->priv;
	unsigned char idx = (offset > 0x2f) ? 
		AVM_IDX_ISAC_REG_HIGH : AVM_IDX_ISAC_REG_LOW;
	unsigned long flags;

	DBG(0x1000, " port %#x, value %#x",
	    offset, value);
	spin_lock_irqsave(&adapter->hw_lock, flags);
	outb(idx, adapter->io + AVM_INDEX);
	outb(value, adapter->io + AVM_DATA + (offset & 0xf));
 	spin_unlock_irqrestore(&adapter->hw_lock, flags);
}