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
typedef  int /*<<< orphan*/  u8 ;
struct bnad_rx_info {int /*<<< orphan*/  rx; } ;
struct TYPE_2__ {int mcast_comp_status; int /*<<< orphan*/  mcast_comp; } ;
struct bnad {TYPE_1__ bnad_completions; int /*<<< orphan*/  bna_lock; struct bnad_rx_info* rx_info; } ;

/* Variables and functions */
 int BNA_CB_SUCCESS ; 
 int ENODEV ; 
 int bna_rx_mcast_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ bnad_bcast_addr ; 
 int /*<<< orphan*/  bnad_cb_rx_mcast_add ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

int
bnad_enable_default_bcast(struct bnad *bnad)
{
	struct bnad_rx_info *rx_info = &bnad->rx_info[0];
	int ret;
	unsigned long flags;

	init_completion(&bnad->bnad_completions.mcast_comp);

	spin_lock_irqsave(&bnad->bna_lock, flags);
	ret = bna_rx_mcast_add(rx_info->rx, (u8 *)bnad_bcast_addr,
				bnad_cb_rx_mcast_add);
	spin_unlock_irqrestore(&bnad->bna_lock, flags);

	if (ret == BNA_CB_SUCCESS)
		wait_for_completion(&bnad->bnad_completions.mcast_comp);
	else
		return -ENODEV;

	if (bnad->bnad_completions.mcast_comp_status != BNA_CB_SUCCESS)
		return -ENODEV;

	return 0;
}