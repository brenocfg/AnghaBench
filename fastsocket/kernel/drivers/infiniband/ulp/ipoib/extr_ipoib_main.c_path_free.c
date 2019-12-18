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
struct net_device {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  raw; } ;
struct TYPE_4__ {TYPE_1__ dgid; } ;
struct ipoib_path {scalar_t__ ah; TYPE_2__ pathrec; int /*<<< orphan*/  queue; } ;

/* Variables and functions */
 struct sk_buff* __skb_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_kfree_skb_irq (struct sk_buff*) ; 
 int /*<<< orphan*/  ipoib_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ipoib_del_neighs_by_gid (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipoib_put_ah (scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct ipoib_path*) ; 
 int /*<<< orphan*/  netdev_priv (struct net_device*) ; 

__attribute__((used)) static void path_free(struct net_device *dev, struct ipoib_path *path)
{
	struct sk_buff *skb;

	while ((skb = __skb_dequeue(&path->queue)))
		dev_kfree_skb_irq(skb);

	ipoib_dbg(netdev_priv(dev), "path_free\n");

	/* remove all neigh connected to this path */
	ipoib_del_neighs_by_gid(dev, path->pathrec.dgid.raw);

	if (path->ah)
		ipoib_put_ah(path->ah);

	kfree(path);
}