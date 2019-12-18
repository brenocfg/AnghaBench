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
struct bnad_rx_info {struct bnad_rx_ctrl* rx_ctrl; int /*<<< orphan*/  rx; } ;
struct bnad_rx_ctrl {int /*<<< orphan*/  ccb; } ;
struct bnad {int num_rx; int num_rxp_per_rx; int /*<<< orphan*/  bna_lock; int /*<<< orphan*/  dim_timer; int /*<<< orphan*/  run_flags; struct bnad_rx_info* rx_info; int /*<<< orphan*/  netdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNAD_DIM_TIMER_FREQ ; 
 int /*<<< orphan*/  BNAD_RF_DIM_TIMER_RUNNING ; 
 int /*<<< orphan*/  bna_rx_dim_update (int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_carrier_ok (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
bnad_dim_timeout(unsigned long data)
{
	struct bnad *bnad = (struct bnad *)data;
	struct bnad_rx_info *rx_info;
	struct bnad_rx_ctrl *rx_ctrl;
	int i, j;
	unsigned long flags;

	if (!netif_carrier_ok(bnad->netdev))
		return;

	spin_lock_irqsave(&bnad->bna_lock, flags);
	for (i = 0; i < bnad->num_rx; i++) {
		rx_info = &bnad->rx_info[i];
		if (!rx_info->rx)
			continue;
		for (j = 0; j < bnad->num_rxp_per_rx; j++) {
			rx_ctrl = &rx_info->rx_ctrl[j];
			if (!rx_ctrl->ccb)
				continue;
			bna_rx_dim_update(rx_ctrl->ccb);
		}
	}

	/* Check for BNAD_CF_DIM_ENABLED, does not eleminate a race */
	if (test_bit(BNAD_RF_DIM_TIMER_RUNNING, &bnad->run_flags))
		mod_timer(&bnad->dim_timer,
			  jiffies + msecs_to_jiffies(BNAD_DIM_TIMER_FREQ));
	spin_unlock_irqrestore(&bnad->bna_lock, flags);
}