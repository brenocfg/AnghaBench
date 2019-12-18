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
typedef  int /*<<< orphan*/  u32 ;
struct bnad_rx_info {struct bnad_rx_ctrl* rx_ctrl; int /*<<< orphan*/  rx; } ;
struct bnad_rx_ctrl {scalar_t__ ccb; } ;
struct bnad {int num_tx; int num_txq_per_tx; int num_rx; int num_rxp_per_rx; struct bnad_rx_info* rx_info; TYPE_1__* tx_info; int /*<<< orphan*/  bna_lock; int /*<<< orphan*/  bna; int /*<<< orphan*/  run_flags; } ;
struct bna_tcb {int /*<<< orphan*/  flags; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {struct bna_tcb** tcb; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNAD_RF_MBOX_IRQ_DISABLED ; 
 int /*<<< orphan*/  BNAD_TXQ_TX_STARTED ; 
 int /*<<< orphan*/  BNA_IS_INTX_DATA_INTR (int /*<<< orphan*/ ) ; 
 scalar_t__ BNA_IS_MBOX_ERR_INTR (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  bna_intr_status_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bna_mbox_handler (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnad_netif_rx_schedule_poll (struct bnad*,scalar_t__) ; 
 int /*<<< orphan*/  bnad_tx_complete (struct bnad*,struct bna_tcb*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static irqreturn_t
bnad_isr(int irq, void *data)
{
	int i, j;
	u32 intr_status;
	unsigned long flags;
	struct bnad *bnad = (struct bnad *)data;
	struct bnad_rx_info *rx_info;
	struct bnad_rx_ctrl *rx_ctrl;
	struct bna_tcb *tcb = NULL;

	spin_lock_irqsave(&bnad->bna_lock, flags);
	if (unlikely(test_bit(BNAD_RF_MBOX_IRQ_DISABLED, &bnad->run_flags))) {
		spin_unlock_irqrestore(&bnad->bna_lock, flags);
		return IRQ_NONE;
	}

	bna_intr_status_get(&bnad->bna, intr_status);

	if (unlikely(!intr_status)) {
		spin_unlock_irqrestore(&bnad->bna_lock, flags);
		return IRQ_NONE;
	}

	if (BNA_IS_MBOX_ERR_INTR(&bnad->bna, intr_status))
		bna_mbox_handler(&bnad->bna, intr_status);

	spin_unlock_irqrestore(&bnad->bna_lock, flags);

	if (!BNA_IS_INTX_DATA_INTR(intr_status))
		return IRQ_HANDLED;

	/* Process data interrupts */
	/* Tx processing */
	for (i = 0; i < bnad->num_tx; i++) {
		for (j = 0; j < bnad->num_txq_per_tx; j++) {
			tcb = bnad->tx_info[i].tcb[j];
			if (tcb && test_bit(BNAD_TXQ_TX_STARTED, &tcb->flags))
				bnad_tx_complete(bnad, bnad->tx_info[i].tcb[j]);
		}
	}
	/* Rx processing */
	for (i = 0; i < bnad->num_rx; i++) {
		rx_info = &bnad->rx_info[i];
		if (!rx_info->rx)
			continue;
		for (j = 0; j < bnad->num_rxp_per_rx; j++) {
			rx_ctrl = &rx_info->rx_ctrl[j];
			if (rx_ctrl->ccb)
				bnad_netif_rx_schedule_poll(bnad,
							    rx_ctrl->ccb);
		}
	}
	return IRQ_HANDLED;
}