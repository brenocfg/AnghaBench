#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct tg3 {TYPE_1__* dev; int /*<<< orphan*/ * napi; } ;
struct sk_buff {struct sk_buff* next; } ;
struct TYPE_6__ {int gso_segs; } ;
struct TYPE_5__ {int features; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct sk_buff*) ; 
 int NETDEV_TX_BUSY ; 
 int NETDEV_TX_OK ; 
 int NETIF_F_TSO ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  netif_stop_queue (TYPE_1__*) ; 
 int /*<<< orphan*/  netif_wake_queue (TYPE_1__*) ; 
 struct sk_buff* skb_gso_segment (struct sk_buff*,int) ; 
 TYPE_2__* skb_shinfo (struct sk_buff*) ; 
 int /*<<< orphan*/  smp_mb () ; 
 int /*<<< orphan*/  tg3_start_xmit (struct sk_buff*,TYPE_1__*) ; 
 scalar_t__ tg3_tx_avail (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int tg3_tso_bug(struct tg3 *tp, struct sk_buff *skb)
{
	struct sk_buff *segs, *nskb;
	u32 frag_cnt_est = skb_shinfo(skb)->gso_segs * 3;

	/* Estimate the number of fragments in the worst case */
	if (unlikely(tg3_tx_avail(&tp->napi[0]) <= frag_cnt_est)) {
		netif_stop_queue(tp->dev);

		/* netif_tx_stop_queue() must be done before checking
		 * checking tx index in tg3_tx_avail() below, because in
		 * tg3_tx(), we update tx index before checking for
		 * netif_tx_queue_stopped().
		 */
		smp_mb();
		if (tg3_tx_avail(&tp->napi[0]) <= frag_cnt_est)
			return NETDEV_TX_BUSY;

		netif_wake_queue(tp->dev);
	}

	segs = skb_gso_segment(skb, tp->dev->features & ~NETIF_F_TSO);
	if (IS_ERR(segs))
		goto tg3_tso_bug_end;

	do {
		nskb = segs;
		segs = segs->next;
		nskb->next = NULL;
		tg3_start_xmit(nskb, tp->dev);
	} while (segs);

tg3_tso_bug_end:
	dev_kfree_skb(skb);

	return NETDEV_TX_OK;
}