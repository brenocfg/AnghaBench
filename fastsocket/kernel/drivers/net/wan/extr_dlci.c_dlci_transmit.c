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
struct dlci_local {TYPE_2__* slave; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;
struct TYPE_4__ {TYPE_1__* netdev_ops; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* ndo_start_xmit ) (struct sk_buff*,TYPE_2__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 struct dlci_local* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  stub1 (struct sk_buff*,TYPE_2__*) ; 

__attribute__((used)) static netdev_tx_t dlci_transmit(struct sk_buff *skb, struct net_device *dev)
{
	struct dlci_local *dlp = netdev_priv(dev);

	if (skb)
		dlp->slave->netdev_ops->ndo_start_xmit(skb, dlp->slave);
	return NETDEV_TX_OK;
}