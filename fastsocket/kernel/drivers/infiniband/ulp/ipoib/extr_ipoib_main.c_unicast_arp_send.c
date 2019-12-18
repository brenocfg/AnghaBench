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
struct TYPE_4__ {int /*<<< orphan*/  tx_dropped; } ;
struct net_device {TYPE_2__ stats; } ;
struct TYPE_3__ {int /*<<< orphan*/  dlid; } ;
struct ipoib_path {int /*<<< orphan*/  queue; scalar_t__ query; scalar_t__ ah; TYPE_1__ pathrec; int /*<<< orphan*/  valid; } ;
struct ipoib_dev_priv {int /*<<< orphan*/  lock; } ;
struct ipoib_cb {scalar_t__ hwaddr; } ;

/* Variables and functions */
 scalar_t__ IPOIB_MAX_PATH_REC_QUEUE ; 
 int /*<<< orphan*/  IPOIB_QPN (scalar_t__) ; 
 int /*<<< orphan*/  __path_add (struct net_device*,struct ipoib_path*) ; 
 struct ipoib_path* __path_find (struct net_device*,scalar_t__) ; 
 int /*<<< orphan*/  __skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  ipoib_dbg (struct ipoib_dev_priv*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipoib_send (struct net_device*,struct sk_buff*,scalar_t__,int /*<<< orphan*/ ) ; 
 struct ipoib_dev_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  path_free (struct net_device*,struct ipoib_path*) ; 
 struct ipoib_path* path_rec_create (struct net_device*,scalar_t__) ; 
 scalar_t__ path_rec_start (struct net_device*,struct ipoib_path*) ; 
 scalar_t__ skb_queue_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void unicast_arp_send(struct sk_buff *skb, struct net_device *dev,
			     struct ipoib_cb *cb)
{
	struct ipoib_dev_priv *priv = netdev_priv(dev);
	struct ipoib_path *path;
	unsigned long flags;

	spin_lock_irqsave(&priv->lock, flags);

	path = __path_find(dev, cb->hwaddr + 4);
	if (!path || !path->valid) {
		int new_path = 0;

		if (!path) {
			path = path_rec_create(dev, cb->hwaddr + 4);
			new_path = 1;
		}
		if (path) {
			__skb_queue_tail(&path->queue, skb);

			if (!path->query && path_rec_start(dev, path)) {
				spin_unlock_irqrestore(&priv->lock, flags);
				if (new_path)
					path_free(dev, path);
				return;
			} else
				__path_add(dev, path);
		} else {
			++dev->stats.tx_dropped;
			dev_kfree_skb_any(skb);
		}

		spin_unlock_irqrestore(&priv->lock, flags);
		return;
	}

	if (path->ah) {
		ipoib_dbg(priv, "Send unicast ARP to %04x\n",
			  be16_to_cpu(path->pathrec.dlid));

		spin_unlock_irqrestore(&priv->lock, flags);
		ipoib_send(dev, skb, path->ah, IPOIB_QPN(cb->hwaddr));
		return;
	} else if ((path->query || !path_rec_start(dev, path)) &&
		   skb_queue_len(&path->queue) < IPOIB_MAX_PATH_REC_QUEUE) {
		__skb_queue_tail(&path->queue, skb);
	} else {
		++dev->stats.tx_dropped;
		dev_kfree_skb_any(skb);
	}

	spin_unlock_irqrestore(&priv->lock, flags);
}