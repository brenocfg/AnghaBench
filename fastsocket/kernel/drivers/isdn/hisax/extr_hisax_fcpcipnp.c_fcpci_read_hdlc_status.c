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
typedef  int /*<<< orphan*/  u32 ;
struct fritz_adapter {int /*<<< orphan*/  hw_lock; scalar_t__ io; } ;

/* Variables and functions */
 scalar_t__ AVM_DATA ; 
 int AVM_IDX_HDLC_1 ; 
 int AVM_IDX_HDLC_2 ; 
 scalar_t__ AVM_INDEX ; 
 scalar_t__ HDLC_STATUS ; 
 int /*<<< orphan*/  inl (scalar_t__) ; 
 int /*<<< orphan*/  outl (int,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static u32 fcpci_read_hdlc_status(struct fritz_adapter *adapter, int nr)
{
	u32 val;
	int idx = nr ? AVM_IDX_HDLC_2 : AVM_IDX_HDLC_1;
	unsigned long flags;

	spin_lock_irqsave(&adapter->hw_lock, flags);
	outl(idx, adapter->io + AVM_INDEX);
	val = inl(adapter->io + AVM_DATA + HDLC_STATUS);
	spin_unlock_irqrestore(&adapter->hw_lock, flags);
	return val;
}