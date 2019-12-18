#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  unhandled; int /*<<< orphan*/  tx; int /*<<< orphan*/  rx; int /*<<< orphan*/  wakeup; int /*<<< orphan*/  sw; int /*<<< orphan*/  alive; int /*<<< orphan*/  sch; int /*<<< orphan*/  hw; } ;
struct il_priv {int inta_mask; int /*<<< orphan*/  status; TYPE_1__ isr_stats; int /*<<< orphan*/ * txq; int /*<<< orphan*/  rxq; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int CSR39_FH_INT_RX_MASK ; 
 int CSR39_FH_INT_TX_MASK ; 
 int /*<<< orphan*/  CSR_FH_INT_STATUS ; 
 int /*<<< orphan*/  CSR_INT ; 
 int CSR_INT_BIT_ALIVE ; 
 int CSR_INT_BIT_FH_RX ; 
 int CSR_INT_BIT_FH_TX ; 
 int CSR_INT_BIT_HW_ERR ; 
 int CSR_INT_BIT_SCD ; 
 int CSR_INT_BIT_SW_ERR ; 
 int CSR_INT_BIT_SW_RX ; 
 int CSR_INT_BIT_WAKEUP ; 
 int /*<<< orphan*/  CSR_INT_MASK ; 
 int /*<<< orphan*/  D_ISR (char*,...) ; 
 int /*<<< orphan*/  FH39_SRVC_CHNL ; 
 int /*<<< orphan*/  FH39_TCSR_CREDIT (int /*<<< orphan*/ ) ; 
 int IL_DL_ISR ; 
 int /*<<< orphan*/  IL_ERR (char*,...) ; 
 int /*<<< orphan*/  IL_WARN (char*,int) ; 
 int /*<<< orphan*/  S_INT_ENABLED ; 
 int _il_rd (struct il_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _il_wr (struct il_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  il3945_rx_handle (struct il_priv*) ; 
 int /*<<< orphan*/  il_disable_interrupts (struct il_priv*) ; 
 int /*<<< orphan*/  il_enable_interrupts (struct il_priv*) ; 
 int il_get_debug_level (struct il_priv*) ; 
 int /*<<< orphan*/  il_irq_handle_error (struct il_priv*) ; 
 int /*<<< orphan*/  il_rx_queue_update_write_ptr (struct il_priv*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  il_txq_update_write_ptr (struct il_priv*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  il_wr (struct il_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
il3945_irq_tasklet(struct il_priv *il)
{
	u32 inta, handled = 0;
	u32 inta_fh;
	unsigned long flags;
#ifdef CONFIG_IWLEGACY_DEBUG
	u32 inta_mask;
#endif

	spin_lock_irqsave(&il->lock, flags);

	/* Ack/clear/reset pending uCode interrupts.
	 * Note:  Some bits in CSR_INT are "OR" of bits in CSR_FH_INT_STATUS,
	 *  and will clear only when CSR_FH_INT_STATUS gets cleared. */
	inta = _il_rd(il, CSR_INT);
	_il_wr(il, CSR_INT, inta);

	/* Ack/clear/reset pending flow-handler (DMA) interrupts.
	 * Any new interrupts that happen after this, either while we're
	 * in this tasklet, or later, will show up in next ISR/tasklet. */
	inta_fh = _il_rd(il, CSR_FH_INT_STATUS);
	_il_wr(il, CSR_FH_INT_STATUS, inta_fh);

#ifdef CONFIG_IWLEGACY_DEBUG
	if (il_get_debug_level(il) & IL_DL_ISR) {
		/* just for debug */
		inta_mask = _il_rd(il, CSR_INT_MASK);
		D_ISR("inta 0x%08x, enabled 0x%08x, fh 0x%08x\n", inta,
		      inta_mask, inta_fh);
	}
#endif

	spin_unlock_irqrestore(&il->lock, flags);

	/* Since CSR_INT and CSR_FH_INT_STATUS reads and clears are not
	 * atomic, make sure that inta covers all the interrupts that
	 * we've discovered, even if FH interrupt came in just after
	 * reading CSR_INT. */
	if (inta_fh & CSR39_FH_INT_RX_MASK)
		inta |= CSR_INT_BIT_FH_RX;
	if (inta_fh & CSR39_FH_INT_TX_MASK)
		inta |= CSR_INT_BIT_FH_TX;

	/* Now service all interrupt bits discovered above. */
	if (inta & CSR_INT_BIT_HW_ERR) {
		IL_ERR("Hardware error detected.  Restarting.\n");

		/* Tell the device to stop sending interrupts */
		il_disable_interrupts(il);

		il->isr_stats.hw++;
		il_irq_handle_error(il);

		handled |= CSR_INT_BIT_HW_ERR;

		return;
	}
#ifdef CONFIG_IWLEGACY_DEBUG
	if (il_get_debug_level(il) & (IL_DL_ISR)) {
		/* NIC fires this, but we don't use it, redundant with WAKEUP */
		if (inta & CSR_INT_BIT_SCD) {
			D_ISR("Scheduler finished to transmit "
			      "the frame/frames.\n");
			il->isr_stats.sch++;
		}

		/* Alive notification via Rx interrupt will do the real work */
		if (inta & CSR_INT_BIT_ALIVE) {
			D_ISR("Alive interrupt\n");
			il->isr_stats.alive++;
		}
	}
#endif
	/* Safely ignore these bits for debug checks below */
	inta &= ~(CSR_INT_BIT_SCD | CSR_INT_BIT_ALIVE);

	/* Error detected by uCode */
	if (inta & CSR_INT_BIT_SW_ERR) {
		IL_ERR("Microcode SW error detected. " "Restarting 0x%X.\n",
		       inta);
		il->isr_stats.sw++;
		il_irq_handle_error(il);
		handled |= CSR_INT_BIT_SW_ERR;
	}

	/* uCode wakes up after power-down sleep */
	if (inta & CSR_INT_BIT_WAKEUP) {
		D_ISR("Wakeup interrupt\n");
		il_rx_queue_update_write_ptr(il, &il->rxq);
		il_txq_update_write_ptr(il, &il->txq[0]);
		il_txq_update_write_ptr(il, &il->txq[1]);
		il_txq_update_write_ptr(il, &il->txq[2]);
		il_txq_update_write_ptr(il, &il->txq[3]);
		il_txq_update_write_ptr(il, &il->txq[4]);
		il_txq_update_write_ptr(il, &il->txq[5]);

		il->isr_stats.wakeup++;
		handled |= CSR_INT_BIT_WAKEUP;
	}

	/* All uCode command responses, including Tx command responses,
	 * Rx "responses" (frame-received notification), and other
	 * notifications from uCode come through here*/
	if (inta & (CSR_INT_BIT_FH_RX | CSR_INT_BIT_SW_RX)) {
		il3945_rx_handle(il);
		il->isr_stats.rx++;
		handled |= (CSR_INT_BIT_FH_RX | CSR_INT_BIT_SW_RX);
	}

	if (inta & CSR_INT_BIT_FH_TX) {
		D_ISR("Tx interrupt\n");
		il->isr_stats.tx++;

		_il_wr(il, CSR_FH_INT_STATUS, (1 << 6));
		il_wr(il, FH39_TCSR_CREDIT(FH39_SRVC_CHNL), 0x0);
		handled |= CSR_INT_BIT_FH_TX;
	}

	if (inta & ~handled) {
		IL_ERR("Unhandled INTA bits 0x%08x\n", inta & ~handled);
		il->isr_stats.unhandled++;
	}

	if (inta & ~il->inta_mask) {
		IL_WARN("Disabled INTA bits 0x%08x were pending\n",
			inta & ~il->inta_mask);
		IL_WARN("   with inta_fh = 0x%08x\n", inta_fh);
	}

	/* Re-enable all interrupts */
	/* only Re-enable if disabled by irq */
	if (test_bit(S_INT_ENABLED, &il->status))
		il_enable_interrupts(il);

#ifdef CONFIG_IWLEGACY_DEBUG
	if (il_get_debug_level(il) & (IL_DL_ISR)) {
		inta = _il_rd(il, CSR_INT);
		inta_mask = _il_rd(il, CSR_INT_MASK);
		inta_fh = _il_rd(il, CSR_FH_INT_STATUS);
		D_ISR("End inta 0x%08x, enabled 0x%08x, fh 0x%08x, "
		      "flags 0x%08lx\n", inta, inta_mask, inta_fh, flags);
	}
#endif
}