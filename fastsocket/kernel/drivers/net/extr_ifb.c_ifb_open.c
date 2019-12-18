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
struct net_device {int dummy; } ;
struct ifb_private {int /*<<< orphan*/  tq; int /*<<< orphan*/  rq; int /*<<< orphan*/  ifb_tasklet; } ;

/* Variables and functions */
 struct ifb_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 int /*<<< orphan*/  ri_tasklet ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static int ifb_open(struct net_device *dev)
{
	struct ifb_private *dp = netdev_priv(dev);

	tasklet_init(&dp->ifb_tasklet, ri_tasklet, (unsigned long)dev);
	skb_queue_head_init(&dp->rq);
	skb_queue_head_init(&dp->tq);
	netif_start_queue(dev);

	return 0;
}