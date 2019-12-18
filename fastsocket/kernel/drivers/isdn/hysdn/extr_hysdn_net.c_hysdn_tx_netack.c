#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct net_local {size_t out_idx; int /*<<< orphan*/  sk_count; TYPE_5__** skbs; TYPE_1__* dev; } ;
struct net_device {int dummy; } ;
struct TYPE_8__ {struct net_local* netif; } ;
typedef  TYPE_3__ hysdn_card ;
struct TYPE_9__ {scalar_t__ len; } ;
struct TYPE_7__ {int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  tx_packets; } ;
struct TYPE_6__ {TYPE_2__ stats; } ;

/* Variables and functions */
 size_t MAX_SKB_BUFFERS ; 
 int /*<<< orphan*/  dev_kfree_skb (TYPE_5__*) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 

void
hysdn_tx_netack(hysdn_card * card)
{
	struct net_local *lp = card->netif;

	if (!lp)
		return;		/* non existing device */


	if (!lp->sk_count)
		return;		/* error condition */

	lp->dev->stats.tx_packets++;
	lp->dev->stats.tx_bytes += lp->skbs[lp->out_idx]->len;

	dev_kfree_skb(lp->skbs[lp->out_idx++]);		/* free skb */
	if (lp->out_idx >= MAX_SKB_BUFFERS)
		lp->out_idx = 0;	/* wrap around */

	if (lp->sk_count-- == MAX_SKB_BUFFERS)	/* dec usage count */
		netif_start_queue((struct net_device *) lp);
}