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
struct netfront_info {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 struct netfront_info* netdev_priv (struct net_device*) ; 
 scalar_t__ netfront_tx_slot_available (struct netfront_info*) ; 
 int /*<<< orphan*/  netif_queue_stopped (struct net_device*) ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void xennet_maybe_wake_tx(struct net_device *dev)
{
	struct netfront_info *np = netdev_priv(dev);

	if (unlikely(netif_queue_stopped(dev)) &&
	    netfront_tx_slot_available(np) &&
	    likely(netif_running(dev)))
		netif_wake_queue(dev);
}