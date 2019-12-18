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
struct TYPE_2__ {scalar_t__ tx_idx; int /*<<< orphan*/  Flags; scalar_t__ tx_skb; int /*<<< orphan*/  timer; } ;
struct isac_hw {TYPE_1__ dch; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLG_BUSY_TIMER ; 
 int /*<<< orphan*/  FLG_TX_BUSY ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 scalar_t__ get_next_dframe (TYPE_1__*) ; 
 int /*<<< orphan*/  isac_fill_fifo (struct isac_hw*) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
isac_retransmit(struct isac_hw *isac)
{
	if (test_and_clear_bit(FLG_BUSY_TIMER, &isac->dch.Flags))
		del_timer(&isac->dch.timer);
	if (test_bit(FLG_TX_BUSY, &isac->dch.Flags)) {
		/* Restart frame */
		isac->dch.tx_idx = 0;
		isac_fill_fifo(isac);
	} else if (isac->dch.tx_skb) { /* should not happen */
		pr_info("%s: tx_skb exist but not busy\n", isac->name);
		test_and_set_bit(FLG_TX_BUSY, &isac->dch.Flags);
		isac->dch.tx_idx = 0;
		isac_fill_fifo(isac);
	} else {
		pr_info("%s: ISAC XDU no TX_BUSY\n", isac->name);
		if (get_next_dframe(&isac->dch))
			isac_fill_fifo(isac);
	}
}