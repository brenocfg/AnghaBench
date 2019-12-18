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
struct bnad_rx_ctrl {int /*<<< orphan*/  rx_intr_ctr; } ;
struct bna_ccb {int /*<<< orphan*/  bnad; scalar_t__ ctrl; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  bnad_netif_rx_schedule_poll (int /*<<< orphan*/ ,struct bna_ccb*) ; 

__attribute__((used)) static irqreturn_t
bnad_msix_rx(int irq, void *data)
{
	struct bna_ccb *ccb = (struct bna_ccb *)data;

	if (ccb) {
		((struct bnad_rx_ctrl *)(ccb->ctrl))->rx_intr_ctr++;
		bnad_netif_rx_schedule_poll(ccb->bnad, ccb);
	}

	return IRQ_HANDLED;
}