#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ tx_idx; TYPE_2__* tx_skb; int /*<<< orphan*/  timer; int /*<<< orphan*/  Flags; } ;
struct isac_hw {TYPE_1__ dch; } ;
struct TYPE_4__ {scalar_t__ len; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLG_BUSY_TIMER ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_kfree_skb (TYPE_2__*) ; 
 scalar_t__ get_next_dframe (TYPE_1__*) ; 
 int /*<<< orphan*/  isac_fill_fifo (struct isac_hw*) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
isac_xpr_irq(struct isac_hw *isac)
{
	if (test_and_clear_bit(FLG_BUSY_TIMER, &isac->dch.Flags))
		del_timer(&isac->dch.timer);
	if (isac->dch.tx_skb && isac->dch.tx_idx < isac->dch.tx_skb->len) {
		isac_fill_fifo(isac);
	} else {
		if (isac->dch.tx_skb)
			dev_kfree_skb(isac->dch.tx_skb);
		if (get_next_dframe(&isac->dch))
			isac_fill_fifo(isac);
	}
}