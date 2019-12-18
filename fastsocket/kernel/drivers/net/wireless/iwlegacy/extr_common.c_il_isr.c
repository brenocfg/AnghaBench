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
struct il_priv {int /*<<< orphan*/  lock; int /*<<< orphan*/  status; int /*<<< orphan*/  irq_tasklet; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  CSR_FH_INT_STATUS ; 
 int /*<<< orphan*/  CSR_INT ; 
 int CSR_INT_BIT_SCD ; 
 int /*<<< orphan*/  CSR_INT_MASK ; 
 int /*<<< orphan*/  D_ISR (char*,...) ; 
 int /*<<< orphan*/  IL_WARN (char*,int) ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  S_INT_ENABLED ; 
 int _il_rd (struct il_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _il_wr (struct il_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  il_enable_interrupts (struct il_priv*) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

irqreturn_t
il_isr(int irq, void *data)
{
	struct il_priv *il = data;
	u32 inta, inta_mask;
	u32 inta_fh;
	unsigned long flags;
	if (!il)
		return IRQ_NONE;

	spin_lock_irqsave(&il->lock, flags);

	/* Disable (but don't clear!) interrupts here to avoid
	 *    back-to-back ISRs and sporadic interrupts from our NIC.
	 * If we have something to service, the tasklet will re-enable ints.
	 * If we *don't* have something, we'll re-enable before leaving here. */
	inta_mask = _il_rd(il, CSR_INT_MASK);	/* just for debug */
	_il_wr(il, CSR_INT_MASK, 0x00000000);

	/* Discover which interrupts are active/pending */
	inta = _il_rd(il, CSR_INT);
	inta_fh = _il_rd(il, CSR_FH_INT_STATUS);

	/* Ignore interrupt if there's nothing in NIC to service.
	 * This may be due to IRQ shared with another device,
	 * or due to sporadic interrupts thrown from our NIC. */
	if (!inta && !inta_fh) {
		D_ISR("Ignore interrupt, inta == 0, inta_fh == 0\n");
		goto none;
	}

	if (inta == 0xFFFFFFFF || (inta & 0xFFFFFFF0) == 0xa5a5a5a0) {
		/* Hardware disappeared. It might have already raised
		 * an interrupt */
		IL_WARN("HARDWARE GONE?? INTA == 0x%08x\n", inta);
		goto unplugged;
	}

	D_ISR("ISR inta 0x%08x, enabled 0x%08x, fh 0x%08x\n", inta, inta_mask,
	      inta_fh);

	inta &= ~CSR_INT_BIT_SCD;

	/* il_irq_tasklet() will service interrupts and re-enable them */
	if (likely(inta || inta_fh))
		tasklet_schedule(&il->irq_tasklet);

unplugged:
	spin_unlock_irqrestore(&il->lock, flags);
	return IRQ_HANDLED;

none:
	/* re-enable interrupts here since we don't have anything to service. */
	/* only Re-enable if disabled by irq */
	if (test_bit(S_INT_ENABLED, &il->status))
		il_enable_interrupts(il);
	spin_unlock_irqrestore(&il->lock, flags);
	return IRQ_NONE;
}