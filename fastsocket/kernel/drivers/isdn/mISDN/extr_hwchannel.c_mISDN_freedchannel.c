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
struct dchannel {int /*<<< orphan*/  rqueue; int /*<<< orphan*/  squeue; int /*<<< orphan*/ * rx_skb; int /*<<< orphan*/ * tx_skb; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_kfree_skb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_scheduled_work () ; 
 int /*<<< orphan*/  skb_queue_purge (int /*<<< orphan*/ *) ; 

int
mISDN_freedchannel(struct dchannel *ch)
{
	if (ch->tx_skb) {
		dev_kfree_skb(ch->tx_skb);
		ch->tx_skb = NULL;
	}
	if (ch->rx_skb) {
		dev_kfree_skb(ch->rx_skb);
		ch->rx_skb = NULL;
	}
	skb_queue_purge(&ch->squeue);
	skb_queue_purge(&ch->rqueue);
	flush_scheduled_work();
	return 0;
}