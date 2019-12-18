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
struct bnad_rx_info {int /*<<< orphan*/  rx_cleanup_work; struct bnad_rx_ctrl* rx_ctrl; } ;
struct bnad_rx_ctrl {struct bna_ccb* ccb; } ;
struct bnad {int /*<<< orphan*/  work_q; } ;
struct bna_rx {scalar_t__ priv; } ;
struct bna_ccb {TYPE_1__** rcb; } ;
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int BNAD_MAX_RXP_PER_RX ; 
 int /*<<< orphan*/  BNAD_RXQ_STARTED ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
bnad_cb_rx_cleanup(struct bnad *bnad, struct bna_rx *rx)
{
	struct bnad_rx_info *rx_info = (struct bnad_rx_info *)rx->priv;
	struct bna_ccb *ccb;
	struct bnad_rx_ctrl *rx_ctrl;
	int i;

	for (i = 0; i < BNAD_MAX_RXP_PER_RX; i++) {
		rx_ctrl = &rx_info->rx_ctrl[i];
		ccb = rx_ctrl->ccb;
		if (!ccb)
			continue;

		clear_bit(BNAD_RXQ_STARTED, &ccb->rcb[0]->flags);

		if (ccb->rcb[1])
			clear_bit(BNAD_RXQ_STARTED, &ccb->rcb[1]->flags);
	}

	queue_work(bnad->work_q, &rx_info->rx_cleanup_work);
}