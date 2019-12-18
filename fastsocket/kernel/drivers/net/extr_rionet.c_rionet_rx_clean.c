#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct rionet_private {int rx_slot; TYPE_2__** rx_skb; int /*<<< orphan*/  mport; } ;
struct TYPE_5__ {int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  rx_dropped; } ;
struct net_device {TYPE_1__ stats; } ;
struct TYPE_6__ {int /*<<< orphan*/  protocol; void* data; } ;

/* Variables and functions */
 int NET_RX_DROP ; 
 int /*<<< orphan*/  RIONET_MAILBOX ; 
 int RIONET_RX_RING_SIZE ; 
 scalar_t__ RIO_MAX_MSG_SIZE ; 
 int /*<<< orphan*/  eth_type_trans (TYPE_2__*,struct net_device*) ; 
 struct rionet_private* netdev_priv (struct net_device*) ; 
 int netif_rx (TYPE_2__*) ; 
 void* rio_get_inb_message (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_put (TYPE_2__*,scalar_t__) ; 

__attribute__((used)) static int rionet_rx_clean(struct net_device *ndev)
{
	int i;
	int error = 0;
	struct rionet_private *rnet = netdev_priv(ndev);
	void *data;

	i = rnet->rx_slot;

	do {
		if (!rnet->rx_skb[i])
			continue;

		if (!(data = rio_get_inb_message(rnet->mport, RIONET_MAILBOX)))
			break;

		rnet->rx_skb[i]->data = data;
		skb_put(rnet->rx_skb[i], RIO_MAX_MSG_SIZE);
		rnet->rx_skb[i]->protocol =
		    eth_type_trans(rnet->rx_skb[i], ndev);
		error = netif_rx(rnet->rx_skb[i]);

		if (error == NET_RX_DROP) {
			ndev->stats.rx_dropped++;
		} else {
			ndev->stats.rx_packets++;
			ndev->stats.rx_bytes += RIO_MAX_MSG_SIZE;
		}

	} while ((i = (i + 1) % RIONET_RX_RING_SIZE) != rnet->rx_slot);

	return i;
}