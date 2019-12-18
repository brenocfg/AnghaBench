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
 scalar_t__ AVM_ISACSX_DATA ; 
 scalar_t__ AVM_ISACSX_INDEX ; 
 int /*<<< orphan*/  DBG (int,char*,unsigned char,unsigned char) ; 
 unsigned char inl (scalar_t__) ; 
 int /*<<< orphan*/  outl (unsigned char,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static unsigned char fcpci2_read_isac(struct isac *isac, unsigned char offset)
{
	struct fritz_adapter *adapter = isac->priv;
	unsigned char val;
	unsigned long flags;

	spin_lock_irqsave(&adapter->hw_lock, flags);
	outl(offset, adapter->io + AVM_ISACSX_INDEX);
	val = inl(adapter->io + AVM_ISACSX_DATA);
 	spin_unlock_irqrestore(&adapter->hw_lock, flags);
	DBG(0x1000, " port %#x, value %#x",
	    offset, val);

	return val;
}