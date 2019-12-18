#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  xmit_lock; int /*<<< orphan*/  super_tx_queue; int /*<<< orphan*/  tqueue; } ;
typedef  TYPE_1__ isdn_net_local ;

/* Variables and functions */
 scalar_t__ in_irq () ; 
 int /*<<< orphan*/  isdn_net_lp_busy (TYPE_1__*) ; 
 int /*<<< orphan*/  isdn_net_writebuf_skb (TYPE_1__*,struct sk_buff*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void isdn_net_write_super(isdn_net_local *lp, struct sk_buff *skb)
{
	if (in_irq()) {
		// we can't grab the lock from irq context, 
		// so we just queue the packet
		skb_queue_tail(&lp->super_tx_queue, skb);
		schedule_work(&lp->tqueue);
		return;
	}

	spin_lock_bh(&lp->xmit_lock);
	if (!isdn_net_lp_busy(lp)) {
		isdn_net_writebuf_skb(lp, skb);
	} else {
		skb_queue_tail(&lp->super_tx_queue, skb);
	}
	spin_unlock_bh(&lp->xmit_lock);
}