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
struct net_local {TYPE_2__* TplFree; } ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;
struct TYPE_4__ {TYPE_1__* NextTPLPtr; } ;
struct TYPE_3__ {scalar_t__ BusyFlag; } ;

/* Variables and functions */
 struct net_local* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  tms380tr_hardware_send_packet (struct sk_buff*,struct net_device*) ; 

__attribute__((used)) static netdev_tx_t tms380tr_send_packet(struct sk_buff *skb,
					      struct net_device *dev)
{
	struct net_local *tp = netdev_priv(dev);
	netdev_tx_t rc;

	rc = tms380tr_hardware_send_packet(skb, dev);
	if(tp->TplFree->NextTPLPtr->BusyFlag)
		netif_stop_queue(dev);
	return rc;
}