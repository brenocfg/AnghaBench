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
struct sk_buff {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  tx_dropped; } ;
struct net_device {TYPE_1__ stats; } ;
struct ipoib_neigh {scalar_t__ daddr; int /*<<< orphan*/  queue; scalar_t__ ah; struct net_device* dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  flushed; int /*<<< orphan*/  entries; } ;
struct ipoib_dev_priv {TYPE_2__ ntbl; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPOIB_NEIGH_TBL_FLUSH ; 
 int /*<<< orphan*/  IPOIB_QPN (scalar_t__) ; 
 struct sk_buff* __skb_dequeue (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  ipoib_cm_destroy_tx (scalar_t__) ; 
 scalar_t__ ipoib_cm_get (struct ipoib_neigh*) ; 
 int /*<<< orphan*/  ipoib_dbg (struct ipoib_dev_priv*,char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ipoib_put_ah (scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct ipoib_neigh*) ; 
 struct ipoib_dev_priv* netdev_priv (struct net_device*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void ipoib_neigh_dtor(struct ipoib_neigh *neigh)
{
	/* neigh reference count was dropprd to zero */
	struct net_device *dev = neigh->dev;
	struct ipoib_dev_priv *priv = netdev_priv(dev);
	struct sk_buff *skb;
	if (neigh->ah)
		ipoib_put_ah(neigh->ah);
	while ((skb = __skb_dequeue(&neigh->queue))) {
		++dev->stats.tx_dropped;
		dev_kfree_skb_any(skb);
	}
	if (ipoib_cm_get(neigh))
		ipoib_cm_destroy_tx(ipoib_cm_get(neigh));
	ipoib_dbg(netdev_priv(dev),
		  "neigh free for %06x %pI6\n",
		  IPOIB_QPN(neigh->daddr),
		  neigh->daddr + 4);
	kfree(neigh);
	if (atomic_dec_and_test(&priv->ntbl.entries)) {
		if (test_bit(IPOIB_NEIGH_TBL_FLUSH, &priv->flags))
			complete(&priv->ntbl.flushed);
	}
}