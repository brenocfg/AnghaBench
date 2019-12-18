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
struct TYPE_4__ {scalar_t__ rsp_cons; TYPE_1__* sring; } ;
struct netfront_info {int /*<<< orphan*/  rx_lock; int /*<<< orphan*/  napi; TYPE_2__ rx; } ;
struct net_device {int dummy; } ;
struct TYPE_3__ {scalar_t__ rsp_event; } ;

/* Variables and functions */
 scalar_t__ RING_HAS_UNCONSUMED_RESPONSES (TYPE_2__*) ; 
 int /*<<< orphan*/  napi_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  napi_schedule (int /*<<< orphan*/ *) ; 
 struct netfront_info* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_carrier_ok (struct net_device*) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xennet_alloc_rx_buffers (struct net_device*) ; 

__attribute__((used)) static int xennet_open(struct net_device *dev)
{
	struct netfront_info *np = netdev_priv(dev);

	napi_enable(&np->napi);

	spin_lock_bh(&np->rx_lock);
	if (netif_carrier_ok(dev)) {
		xennet_alloc_rx_buffers(dev);
		np->rx.sring->rsp_event = np->rx.rsp_cons + 1;
		if (RING_HAS_UNCONSUMED_RESPONSES(&np->rx))
			napi_schedule(&np->napi);
	}
	spin_unlock_bh(&np->rx_lock);

	netif_start_queue(dev);

	return 0;
}