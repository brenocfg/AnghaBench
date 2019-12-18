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
struct iwl_trans_pcie {size_t ict_index; int inta_mask; int inta; int /*<<< orphan*/  irq_lock; int /*<<< orphan*/  status; scalar_t__* ict_tbl; int /*<<< orphan*/  use_ict; } ;
struct iwl_trans {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  CSR_INT_MASK ; 
 int /*<<< orphan*/  ICT_COUNT ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  IRQ_WAKE_THREAD ; 
 int /*<<< orphan*/  IWL_DEBUG_ISR (struct iwl_trans*,char*,...) ; 
 struct iwl_trans_pcie* IWL_TRANS_GET_PCIE_TRANS (struct iwl_trans*) ; 
 int /*<<< orphan*/  STATUS_INT_ENABLED ; 
 int /*<<< orphan*/  iwl_enable_interrupts (struct iwl_trans*) ; 
 int /*<<< orphan*/  iwl_pcie_isr (int,void*) ; 
 size_t iwl_queue_inc_wrap (size_t,int /*<<< orphan*/ ) ; 
 int iwl_read32 (struct iwl_trans*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_write32 (struct iwl_trans*,int /*<<< orphan*/ ,int) ; 
 int le32_to_cpu (scalar_t__) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_iwlwifi_dev_ict_read (int /*<<< orphan*/ ,size_t,int) ; 
 int /*<<< orphan*/  trace_iwlwifi_dev_irq (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

irqreturn_t iwl_pcie_isr_ict(int irq, void *data)
{
	struct iwl_trans *trans = data;
	struct iwl_trans_pcie *trans_pcie;
	u32 inta, inta_mask;
	u32 val = 0;
	u32 read;
	unsigned long flags;

	if (!trans)
		return IRQ_NONE;

	trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);

	spin_lock_irqsave(&trans_pcie->irq_lock, flags);

	/* dram interrupt table not set yet,
	 * use legacy interrupt.
	 */
	if (unlikely(!trans_pcie->use_ict)) {
		irqreturn_t ret = iwl_pcie_isr(irq, data);
		spin_unlock_irqrestore(&trans_pcie->irq_lock, flags);
		return ret;
	}

	trace_iwlwifi_dev_irq(trans->dev);

	/* Disable (but don't clear!) interrupts here to avoid
	 * back-to-back ISRs and sporadic interrupts from our NIC.
	 * If we have something to service, the tasklet will re-enable ints.
	 * If we *don't* have something, we'll re-enable before leaving here.
	 */
	inta_mask = iwl_read32(trans, CSR_INT_MASK);
	iwl_write32(trans, CSR_INT_MASK, 0x00000000);

	/* Ignore interrupt if there's nothing in NIC to service.
	 * This may be due to IRQ shared with another device,
	 * or due to sporadic interrupts thrown from our NIC. */
	read = le32_to_cpu(trans_pcie->ict_tbl[trans_pcie->ict_index]);
	trace_iwlwifi_dev_ict_read(trans->dev, trans_pcie->ict_index, read);
	if (!read) {
		IWL_DEBUG_ISR(trans, "Ignore interrupt, inta == 0\n");
		goto none;
	}

	/*
	 * Collect all entries up to the first 0, starting from ict_index;
	 * note we already read at ict_index.
	 */
	do {
		val |= read;
		IWL_DEBUG_ISR(trans, "ICT index %d value 0x%08X\n",
				trans_pcie->ict_index, read);
		trans_pcie->ict_tbl[trans_pcie->ict_index] = 0;
		trans_pcie->ict_index =
			iwl_queue_inc_wrap(trans_pcie->ict_index, ICT_COUNT);

		read = le32_to_cpu(trans_pcie->ict_tbl[trans_pcie->ict_index]);
		trace_iwlwifi_dev_ict_read(trans->dev, trans_pcie->ict_index,
					   read);
	} while (read);

	/* We should not get this value, just ignore it. */
	if (val == 0xffffffff)
		val = 0;

	/*
	 * this is a w/a for a h/w bug. the h/w bug may cause the Rx bit
	 * (bit 15 before shifting it to 31) to clear when using interrupt
	 * coalescing. fortunately, bits 18 and 19 stay set when this happens
	 * so we use them to decide on the real state of the Rx bit.
	 * In order words, bit 15 is set if bit 18 or bit 19 are set.
	 */
	if (val & 0xC0000)
		val |= 0x8000;

	inta = (0xff & val) | ((0xff00 & val) << 16);
	IWL_DEBUG_ISR(trans, "ISR inta 0x%08x, enabled 0x%08x ict 0x%08x\n",
		      inta, inta_mask, val);

	inta &= trans_pcie->inta_mask;
	trans_pcie->inta |= inta;

	/* iwl_pcie_tasklet() will service interrupts and re-enable them */
	if (likely(inta)) {
		spin_unlock_irqrestore(&trans_pcie->irq_lock, flags);
		return IRQ_WAKE_THREAD;
	} else if (test_bit(STATUS_INT_ENABLED, &trans_pcie->status) &&
		 !trans_pcie->inta) {
		/* Allow interrupt if was disabled by this handler and
		 * no tasklet was schedules, We should not enable interrupt,
		 * tasklet will enable it.
		 */
		iwl_enable_interrupts(trans);
	}

	spin_unlock_irqrestore(&trans_pcie->irq_lock, flags);
	return IRQ_HANDLED;

 none:
	/* re-enable interrupts here since we don't have anything to service.
	 * only Re-enable if disabled by irq.
	 */
	if (test_bit(STATUS_INT_ENABLED, &trans_pcie->status) &&
	    !trans_pcie->inta)
		iwl_enable_interrupts(trans);

	spin_unlock_irqrestore(&trans_pcie->irq_lock, flags);
	return IRQ_NONE;
}