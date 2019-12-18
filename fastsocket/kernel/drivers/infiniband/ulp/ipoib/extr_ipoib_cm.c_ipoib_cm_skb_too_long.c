#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct net_device {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  skb_task; int /*<<< orphan*/  skb_queue; } ;
struct ipoib_dev_priv {TYPE_2__ cm; } ;
struct TYPE_7__ {TYPE_1__* ops; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* update_pmtu ) (TYPE_3__*,unsigned int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ipoib_workqueue ; 
 struct ipoib_dev_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_3__* skb_dst (struct sk_buff*) ; 
 int skb_queue_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,unsigned int) ; 

void ipoib_cm_skb_too_long(struct net_device *dev, struct sk_buff *skb,
			   unsigned int mtu)
{
	struct ipoib_dev_priv *priv = netdev_priv(dev);
	int e = skb_queue_empty(&priv->cm.skb_queue);

	if (skb_dst(skb))
		skb_dst(skb)->ops->update_pmtu(skb_dst(skb), mtu);

	skb_queue_tail(&priv->cm.skb_queue, skb);
	if (e)
		queue_work(ipoib_workqueue, &priv->cm.skb_task);
}